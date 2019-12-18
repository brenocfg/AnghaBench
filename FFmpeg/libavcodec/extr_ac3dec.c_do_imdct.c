#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  (* imdct_half ) (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
struct TYPE_9__ {int /*<<< orphan*/  (* imdct_half ) (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
struct TYPE_8__ {int /*<<< orphan*/ * tmp_output; int /*<<< orphan*/ ** delay; int /*<<< orphan*/  window; int /*<<< orphan*/ * outptr; TYPE_1__* fdsp; int /*<<< orphan*/ ** transform_coeffs; TYPE_3__ imdct_512; TYPE_4__ imdct_256; scalar_t__* block_switch; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* vector_fmul_window ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* vector_fmul_window_scaled ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ;} ;
typedef  int /*<<< orphan*/  FFTSample ;
typedef  TYPE_2__ AC3DecodeContext ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub4 (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub5 (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub6 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  stub7 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void do_imdct(AC3DecodeContext *s, int channels, int offset)
{
    int ch;

    for (ch = 1; ch <= channels; ch++) {
        if (s->block_switch[ch]) {
            int i;
            FFTSample *x = s->tmp_output + 128;
            for (i = 0; i < 128; i++)
                x[i] = s->transform_coeffs[ch][2 * i];
            s->imdct_256.imdct_half(&s->imdct_256, s->tmp_output, x);
#if USE_FIXED
            s->fdsp->vector_fmul_window_scaled(s->outptr[ch - 1], s->delay[ch - 1 + offset],
                                       s->tmp_output, s->window, 128, 8);
#else
            s->fdsp->vector_fmul_window(s->outptr[ch - 1], s->delay[ch - 1 + offset],
                                       s->tmp_output, s->window, 128);
#endif
            for (i = 0; i < 128; i++)
                x[i] = s->transform_coeffs[ch][2 * i + 1];
            s->imdct_256.imdct_half(&s->imdct_256, s->delay[ch - 1 + offset], x);
        } else {
            s->imdct_512.imdct_half(&s->imdct_512, s->tmp_output, s->transform_coeffs[ch]);
#if USE_FIXED
            s->fdsp->vector_fmul_window_scaled(s->outptr[ch - 1], s->delay[ch - 1 + offset],
                                       s->tmp_output, s->window, 128, 8);
#else
            s->fdsp->vector_fmul_window(s->outptr[ch - 1], s->delay[ch - 1 + offset],
                                       s->tmp_output, s->window, 128);
#endif
            memcpy(s->delay[ch - 1 + offset], s->tmp_output + 128, 128 * sizeof(FFTSample));
        }
    }
}