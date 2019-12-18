#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {void** lin_lut; void** delin_lut; TYPE_2__* out_txchr; TYPE_1__* in_txchr; } ;
struct TYPE_6__ {double alpha; double beta; double gamma; double delta; } ;
struct TYPE_5__ {double alpha; double beta; double gamma; double delta; } ;
typedef  TYPE_3__ ColorSpaceContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 void* av_clip_int16 (int /*<<< orphan*/ ) ; 
 void** av_malloc (int) ; 
 int /*<<< orphan*/  lrint (double) ; 
 double pow (double,double) ; 

__attribute__((used)) static int fill_gamma_table(ColorSpaceContext *s)
{
    int n;
    double in_alpha = s->in_txchr->alpha, in_beta = s->in_txchr->beta;
    double in_gamma = s->in_txchr->gamma, in_delta = s->in_txchr->delta;
    double in_ialpha = 1.0 / in_alpha, in_igamma = 1.0 / in_gamma, in_idelta = 1.0 / in_delta;
    double out_alpha = s->out_txchr->alpha, out_beta = s->out_txchr->beta;
    double out_gamma = s->out_txchr->gamma, out_delta = s->out_txchr->delta;

    s->lin_lut = av_malloc(sizeof(*s->lin_lut) * 32768 * 2);
    if (!s->lin_lut)
        return AVERROR(ENOMEM);
    s->delin_lut = &s->lin_lut[32768];
    for (n = 0; n < 32768; n++) {
        double v = (n - 2048.0) / 28672.0, d, l;

        // delinearize
        if (v <= -out_beta) {
            d = -out_alpha * pow(-v, out_gamma) + (out_alpha - 1.0);
        } else if (v < out_beta) {
            d = out_delta * v;
        } else {
            d = out_alpha * pow(v, out_gamma) - (out_alpha - 1.0);
        }
        s->delin_lut[n] = av_clip_int16(lrint(d * 28672.0));

        // linearize
        if (v <= -in_beta * in_delta) {
            l = -pow((1.0 - in_alpha - v) * in_ialpha, in_igamma);
        } else if (v < in_beta * in_delta) {
            l = v * in_idelta;
        } else {
            l = pow((v + in_alpha - 1.0) * in_ialpha, in_igamma);
        }
        s->lin_lut[n] = av_clip_int16(lrint(l * 28672.0));
    }

    return 0;
}