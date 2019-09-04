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
struct kissf_fftr_state {int dummy; } ;
typedef  TYPE_1__* kissf_fftr_cfg ;
typedef  int /*<<< orphan*/  kissf_fft_cpx ;
typedef  int /*<<< orphan*/ * kissf_fft_cfg ;
struct TYPE_3__ {int /*<<< orphan*/ * super_twiddles; int /*<<< orphan*/ * substate; int /*<<< orphan*/ * tmpbuf; } ;

/* Variables and functions */
 scalar_t__ KISSF_FFT_MALLOC (size_t) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  kf_cexp (int /*<<< orphan*/ *,double) ; 
 int /*<<< orphan*/  kissf_fft_alloc (int,int,int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  stderr ; 

kissf_fftr_cfg kissf_fftr_alloc(int nfft,int inverse_fft,void * mem,size_t * lenmem)
{
    int i;
    kissf_fftr_cfg st = NULL;
    size_t subsize, memneeded;

    if (nfft & 1) {
        fprintf(stderr,"Real FFT optimization must be even.\n");
        return NULL;
    }
    nfft >>= 1;

    kissf_fft_alloc (nfft, inverse_fft, NULL, &subsize);
    memneeded = sizeof(struct kissf_fftr_state) + subsize + sizeof(kissf_fft_cpx) * ( nfft * 3 / 2);

    if (lenmem == NULL) {
        st = (kissf_fftr_cfg) KISSF_FFT_MALLOC (memneeded);
    } else {
        if (*lenmem >= memneeded)
            st = (kissf_fftr_cfg) mem;
        *lenmem = memneeded;
    }
    if (!st)
        return NULL;

    st->substate = (kissf_fft_cfg) (st + 1); /*just beyond kissf_fftr_state struct */
    st->tmpbuf = (kissf_fft_cpx *) (((char *) st->substate) + subsize);
    st->super_twiddles = st->tmpbuf + nfft;
    kissf_fft_alloc(nfft, inverse_fft, st->substate, &subsize);

    for (i = 0; i < nfft/2; ++i) {
        double phase =
            -3.14159265358979323846264338327 * ((double) (i+1) / nfft + .5);
        if (inverse_fft)
            phase *= -1;
        kf_cexp (st->super_twiddles+i,phase);
    }
    return st;
}