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
struct TYPE_3__ {int dimReal; int dimOther; int /*<<< orphan*/  cfg_r; int /*<<< orphan*/  cfg_nd; scalar_t__ tmpbuf; } ;

/* Variables and functions */
 int MAX (int,int) ; 
 int /*<<< orphan*/  kissf_fftnd (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kissf_fftri (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void kissf_fftndri(kissf_fftndr_cfg st,const kissf_fft_cpx *freqdata,kissf_fft_scalar *timedata)
{
    int k1,k2;
    int dimReal = st->dimReal;
    int dimOther = st->dimOther;
    int nrbins = dimReal/2+1;
    kissf_fft_cpx * tmp1 = (kissf_fft_cpx*)st->tmpbuf; 
    kissf_fft_cpx * tmp2 = tmp1 + MAX(nrbins,dimOther);

    for (k2=0;k2<nrbins;++k2) {
        for (k1=0;k1<dimOther;++k1) 
            tmp1[k1] = freqdata[ k1*(nrbins) + k2 ];
        kissf_fftnd(st->cfg_nd, tmp1, tmp2+k2*dimOther);
    }

    for (k1=0;k1<dimOther;++k1) {
        for (k2=0;k2<nrbins;++k2)
            tmp1[k2] = tmp2[ k2*dimOther+k1 ];
        kissf_fftri( st->cfg_r,tmp1,timedata + k1*dimReal);
    }
}