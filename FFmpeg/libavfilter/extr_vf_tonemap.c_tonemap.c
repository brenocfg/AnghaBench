#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ desat; int tonemap; float param; TYPE_2__* coeffs; } ;
typedef  TYPE_3__ TonemapContext ;
struct TYPE_14__ {int* linesize; scalar_t__* data; } ;
struct TYPE_13__ {TYPE_1__* comp; } ;
struct TYPE_11__ {float const cr; float const cg; float const cb; } ;
struct TYPE_10__ {int step; } ;
typedef  TYPE_4__ AVPixFmtDescriptor ;
typedef  TYPE_5__ AVFrame ;

/* Variables and functions */
 float FFMAX (float,int) ; 
 float FFMAX3 (float,float,float) ; 
 float MIX (float const,float,float) ; 
#define  TONEMAP_CLIP 134 
#define  TONEMAP_GAMMA 133 
#define  TONEMAP_HABLE 132 
#define  TONEMAP_LINEAR 131 
#define  TONEMAP_MOBIUS 130 
#define  TONEMAP_NONE 129 
#define  TONEMAP_REINHARD 128 
 float av_clipf (float,int /*<<< orphan*/ ,float) ; 
 float hable (double) ; 
 float mobius (float,float,double) ; 
 float pow (float,float) ; 

__attribute__((used)) static void tonemap(TonemapContext *s, AVFrame *out, const AVFrame *in,
                    const AVPixFmtDescriptor *desc, int x, int y, double peak)
{
    const float *r_in = (const float *)(in->data[0] + x * desc->comp[0].step + y * in->linesize[0]);
    const float *b_in = (const float *)(in->data[1] + x * desc->comp[1].step + y * in->linesize[1]);
    const float *g_in = (const float *)(in->data[2] + x * desc->comp[2].step + y * in->linesize[2]);
    float *r_out = (float *)(out->data[0] + x * desc->comp[0].step + y * out->linesize[0]);
    float *b_out = (float *)(out->data[1] + x * desc->comp[1].step + y * out->linesize[1]);
    float *g_out = (float *)(out->data[2] + x * desc->comp[2].step + y * out->linesize[2]);
    float sig, sig_orig;

    /* load values */
    *r_out = *r_in;
    *b_out = *b_in;
    *g_out = *g_in;

    /* desaturate to prevent unnatural colors */
    if (s->desat > 0) {
        float luma = s->coeffs->cr * *r_in + s->coeffs->cg * *g_in + s->coeffs->cb * *b_in;
        float overbright = FFMAX(luma - s->desat, 1e-6) / FFMAX(luma, 1e-6);
        *r_out = MIX(*r_in, luma, overbright);
        *g_out = MIX(*g_in, luma, overbright);
        *b_out = MIX(*b_in, luma, overbright);
    }

    /* pick the brightest component, reducing the value range as necessary
     * to keep the entire signal in range and preventing discoloration due to
     * out-of-bounds clipping */
    sig = FFMAX(FFMAX3(*r_out, *g_out, *b_out), 1e-6);
    sig_orig = sig;

    switch(s->tonemap) {
    default:
    case TONEMAP_NONE:
        // do nothing
        break;
    case TONEMAP_LINEAR:
        sig = sig * s->param / peak;
        break;
    case TONEMAP_GAMMA:
        sig = sig > 0.05f ? pow(sig / peak, 1.0f / s->param)
                          : sig * pow(0.05f / peak, 1.0f / s->param) / 0.05f;
        break;
    case TONEMAP_CLIP:
        sig = av_clipf(sig * s->param, 0, 1.0f);
        break;
    case TONEMAP_HABLE:
        sig = hable(sig) / hable(peak);
        break;
    case TONEMAP_REINHARD:
        sig = sig / (sig + s->param) * (peak + s->param) / peak;
        break;
    case TONEMAP_MOBIUS:
        sig = mobius(sig, s->param, peak);
        break;
    }

    /* apply the computed scale factor to the color,
     * linearly to prevent discoloration */
    *r_out *= sig / sig_orig;
    *g_out *= sig / sig_orig;
    *b_out *= sig / sig_orig;
}