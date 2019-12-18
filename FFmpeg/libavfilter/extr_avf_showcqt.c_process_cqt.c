#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {float re; float im; } ;
struct TYPE_7__ {float member_0; float member_1; float re; float im; } ;
struct TYPE_6__ {int cqt_len; float* h_buf; float* bar_v_buf; int fcount; int width; float* rcp_h_buf; float* sono_v_buf; scalar_t__ format; int /*<<< orphan*/  cscheme_v; int /*<<< orphan*/  cmatrix; int /*<<< orphan*/  sono_g; TYPE_3__* cqt_result; int /*<<< orphan*/  c_buf; int /*<<< orphan*/  bar_g; int /*<<< orphan*/  sono_count; } ;
typedef  TYPE_1__ ShowCQTContext ;
typedef  TYPE_2__ FFTComplex ;

/* Variables and functions */
 scalar_t__ AV_PIX_FMT_RGB24 ; 
 float calculate_gamma (float,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rgb_from_cqt (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  yuv_from_cqt (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void process_cqt(ShowCQTContext *s)
{
    int x, i;
    if (!s->sono_count) {
        for (x = 0; x < s->cqt_len; x++) {
            s->h_buf[x] = s->bar_v_buf[x] * 0.5f * (s->cqt_result[x].re + s->cqt_result[x].im);
        }
        if (s->fcount > 1) {
            float rcp_fcount = 1.0f / s->fcount;
            for (x = 0; x < s->width; x++) {
                float h = 0.0f;
                for (i = 0; i < s->fcount; i++)
                    h += s->h_buf[s->fcount * x + i];
                s->h_buf[x] = rcp_fcount * h;
            }
        }
        for (x = 0; x < s->width; x++) {
            s->h_buf[x] = calculate_gamma(s->h_buf[x], s->bar_g);
            s->rcp_h_buf[x] = 1.0f / (s->h_buf[x] + 0.0001f);
        }
    }

    for (x = 0; x < s->cqt_len; x++) {
        s->cqt_result[x].re *= s->sono_v_buf[x];
        s->cqt_result[x].im *= s->sono_v_buf[x];
    }

    if (s->fcount > 1) {
        float rcp_fcount = 1.0f / s->fcount;
        for (x = 0; x < s->width; x++) {
            FFTComplex result = {0.0f, 0.0f};
            for (i = 0; i < s->fcount; i++) {
                result.re += s->cqt_result[s->fcount * x + i].re;
                result.im += s->cqt_result[s->fcount * x + i].im;
            }
            s->cqt_result[x].re = rcp_fcount * result.re;
            s->cqt_result[x].im = rcp_fcount * result.im;
        }
    }

    if (s->format == AV_PIX_FMT_RGB24)
        rgb_from_cqt(s->c_buf, s->cqt_result, s->sono_g, s->width, s->cscheme_v);
    else
        yuv_from_cqt(s->c_buf, s->cqt_result, s->sono_g, s->width, s->cmatrix, s->cscheme_v);
}