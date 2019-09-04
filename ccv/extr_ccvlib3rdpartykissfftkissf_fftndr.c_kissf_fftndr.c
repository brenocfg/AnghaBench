#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int nrbins ;
typedef  TYPE_1__* kissf_fftndr_cfg ;
typedef  int /*<<< orphan*/  kissf_fft_scalar ;
typedef  int /*<<< orphan*/  kissf_fft_cpx ;
struct TYPE_3__ {int dimReal; int dimOther; int /*<<< orphan*/  cfg_nd; int /*<<< orphan*/  cfg_r; scalar_t__ tmpbuf; } ;

/* Variables and functions */
 int MAX (int,int) ; 
 int /*<<< orphan*/  kissf_fftnd (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kissf_fftr (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

void kissf_fftndr(kissf_fftndr_cfg st,const kissf_fft_scalar *timedata,kissf_fft_cpx *freqdata)
{
    int k1,k2;
    int dimReal = st->dimReal;
    int dimOther = st->dimOther;
    int nrbins = dimReal/2+1;

    kissf_fft_cpx * tmp1 = (kissf_fft_cpx*)st->tmpbuf; 
    kissf_fft_cpx * tmp2 = tmp1 + MAX(nrbins,dimOther);

    // timedata is N0 x N1 x ... x Nk real

    // take a real chunk of data, fft it and place the output at correct intervals
    for (k1=0;k1<dimOther;++k1) {
        kissf_fftr( st->cfg_r, timedata + k1*dimReal , tmp1 ); // tmp1 now holds nrbins complex points
        for (k2=0;k2<nrbins;++k2)
           tmp2[ k2*dimOther+k1 ] = tmp1[k2];
    }

    for (k2=0;k2<nrbins;++k2) {
        kissf_fftnd(st->cfg_nd, tmp2+k2*dimOther, tmp1);  // tmp1 now holds dimOther complex points
        for (k1=0;k1<dimOther;++k1) 
            freqdata[ k1*(nrbins) + k2] = tmp1[k1];
    }
}