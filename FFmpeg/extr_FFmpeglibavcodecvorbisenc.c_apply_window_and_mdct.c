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
struct TYPE_5__ {float** win; int* log2_blocksize; int channels; float* samples; scalar_t__ coeffs; TYPE_3__* mdct; TYPE_2__* fdsp; } ;
typedef  TYPE_1__ vorbis_enc_context ;
struct TYPE_7__ {int /*<<< orphan*/  (* mdct_calc ) (TYPE_3__*,scalar_t__,float*) ;} ;
struct TYPE_6__ {int /*<<< orphan*/  (* vector_fmul_scalar ) (float*,float*,int,int) ;int /*<<< orphan*/  (* vector_fmul_reverse ) (float*,float*,float const*,int) ;int /*<<< orphan*/  (* vector_fmul ) (float*,float*,float const*,int) ;} ;
typedef  TYPE_2__ AVFloatDSPContext ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (float*,float*,float const*,int) ; 
 int /*<<< orphan*/  stub2 (float*,float*,int,int) ; 
 int /*<<< orphan*/  stub3 (float*,float*,float const*,int) ; 
 int /*<<< orphan*/  stub4 (float*,float*,int,int) ; 
 int /*<<< orphan*/  stub5 (TYPE_3__*,scalar_t__,float*) ; 

__attribute__((used)) static int apply_window_and_mdct(vorbis_enc_context *venc)
{
    int channel;
    const float * win = venc->win[1];
    int window_len = 1 << (venc->log2_blocksize[1] - 1);
    float n = (float)(1 << venc->log2_blocksize[1]) / 4.0;
    AVFloatDSPContext *fdsp = venc->fdsp;

    for (channel = 0; channel < venc->channels; channel++) {
        float *offset = venc->samples + channel * window_len * 2;

        fdsp->vector_fmul(offset, offset, win, window_len);
        fdsp->vector_fmul_scalar(offset, offset, 1/n, window_len);

        offset += window_len;

        fdsp->vector_fmul_reverse(offset, offset, win, window_len);
        fdsp->vector_fmul_scalar(offset, offset, 1/n, window_len);

        venc->mdct[1].mdct_calc(&venc->mdct[1], venc->coeffs + channel * window_len,
                     venc->samples + channel * window_len * 2);
    }
    return 1;
}