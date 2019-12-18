#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* kiss_fftr_cfg ;
typedef  int /*<<< orphan*/  kiss_fft_scalar ;
struct TYPE_18__ {int r; int i; } ;
typedef  TYPE_2__ kiss_fft_cpx ;
struct TYPE_19__ {scalar_t__ inverse; int nfft; } ;
struct TYPE_17__ {TYPE_2__* tmpbuf; TYPE_5__* substate; int /*<<< orphan*/ * super_twiddles; } ;

/* Variables and functions */
 int /*<<< orphan*/  C_ADD (TYPE_2__,TYPE_2__,TYPE_2__) ; 
 int /*<<< orphan*/  C_FIXDIV (TYPE_2__,int) ; 
 int /*<<< orphan*/  C_MUL (TYPE_2__,TYPE_2__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  C_SUB (TYPE_2__,TYPE_2__,TYPE_2__) ; 
 int _mm_set1_ps (double) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  kiss_fft (TYPE_5__*,TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  stderr ; 

void kiss_fftri(kiss_fftr_cfg st,const kiss_fft_cpx *freqdata,kiss_fft_scalar *timedata)
{
    /* input buffer timedata is stored row-wise */
    int k, ncfft;

    if (st->substate->inverse == 0) {
        fprintf (stderr, "kiss fft usage error: improper alloc\n");
        exit (1);
    }

    ncfft = st->substate->nfft;

    st->tmpbuf[0].r = freqdata[0].r + freqdata[ncfft].r;
    st->tmpbuf[0].i = freqdata[0].r - freqdata[ncfft].r;
    C_FIXDIV(st->tmpbuf[0],2);

    for (k = 1; k <= ncfft / 2; ++k) {
        kiss_fft_cpx fk, fnkc, fek, fok, tmp;
        fk = freqdata[k];
        fnkc.r = freqdata[ncfft - k].r;
        fnkc.i = -freqdata[ncfft - k].i;
        C_FIXDIV( fk , 2 );
        C_FIXDIV( fnkc , 2 );

        C_ADD (fek, fk, fnkc);
        C_SUB (tmp, fk, fnkc);
        C_MUL (fok, tmp, st->super_twiddles[k-1]);
        C_ADD (st->tmpbuf[k],     fek, fok);
        C_SUB (st->tmpbuf[ncfft - k], fek, fok);
#ifdef USE_SIMD        
        st->tmpbuf[ncfft - k].i *= _mm_set1_ps(-1.0);
#else
        st->tmpbuf[ncfft - k].i *= -1;
#endif
    }
    kiss_fft (st->substate, st->tmpbuf, (kiss_fft_cpx *) timedata);
}