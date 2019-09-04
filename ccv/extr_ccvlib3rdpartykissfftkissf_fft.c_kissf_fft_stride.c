#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  const kissf_fft_cpx ;
typedef  TYPE_1__* kissf_fft_cfg ;
struct TYPE_4__ {int nfft; int /*<<< orphan*/  factors; } ;

/* Variables and functions */
 scalar_t__ KISSF_FFT_TMP_ALLOC (int) ; 
 int /*<<< orphan*/  KISSF_FFT_TMP_FREE (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  kf_work (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int,int,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int) ; 

void kissf_fft_stride(kissf_fft_cfg st,const kissf_fft_cpx *fin,kissf_fft_cpx *fout,int in_stride)
{
    if (fin == fout) {
        //NOTE: this is not really an in-place FFT algorithm.
        //It just performs an out-of-place FFT into a temp buffer
        kissf_fft_cpx * tmpbuf = (kissf_fft_cpx*)KISSF_FFT_TMP_ALLOC( sizeof(kissf_fft_cpx)*st->nfft);
        kf_work(tmpbuf,fin,1,in_stride, st->factors,st);
        memcpy(fout,tmpbuf,sizeof(kissf_fft_cpx)*st->nfft);
        KISSF_FFT_TMP_FREE(tmpbuf);
    }else{
        kf_work( fout, fin, 1,in_stride, st->factors,st );
    }
}