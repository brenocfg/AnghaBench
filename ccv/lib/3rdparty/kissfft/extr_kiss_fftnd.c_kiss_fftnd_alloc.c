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
struct kiss_fftnd_state {int dummy; } ;
typedef  TYPE_1__* kiss_fftnd_cfg ;
typedef  int /*<<< orphan*/  kiss_fft_cpx ;
typedef  int /*<<< orphan*/  kiss_fft_cfg ;
struct TYPE_3__ {int dimprod; int ndims; int* dims; int /*<<< orphan*/ * states; int /*<<< orphan*/ * tmpbuf; } ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  kiss_fft_alloc (int const,int,char*,size_t*) ; 
 scalar_t__ malloc (size_t) ; 
 int /*<<< orphan*/  stderr ; 

kiss_fftnd_cfg kiss_fftnd_alloc(const int *dims,int ndims,int inverse_fft,void*mem,size_t*lenmem)
{
    kiss_fftnd_cfg st = NULL;
    int i;
    int dimprod=1;
    size_t memneeded = sizeof(struct kiss_fftnd_state);
    char * ptr;

    for (i=0;i<ndims;++i) {
        size_t sublen=0;
        kiss_fft_alloc (dims[i], inverse_fft, NULL, &sublen);
        memneeded += sublen;   /* st->states[i] */
        dimprod *= dims[i];
    }
    memneeded += sizeof(int) * ndims;/*  st->dims */
    memneeded += sizeof(void*) * ndims;/* st->states  */
    memneeded += sizeof(kiss_fft_cpx) * dimprod; /* st->tmpbuf */

    if (lenmem == NULL) {/* allocate for the caller*/
        st = (kiss_fftnd_cfg) malloc (memneeded);
    } else { /* initialize supplied buffer if big enough */
        if (*lenmem >= memneeded)
            st = (kiss_fftnd_cfg) mem;
        *lenmem = memneeded; /*tell caller how big struct is (or would be) */
    }
    if (!st)
        return NULL; /*malloc failed or buffer too small */

    st->dimprod = dimprod;
    st->ndims = ndims;
    ptr=(char*)(st+1);

    st->states = (kiss_fft_cfg *)ptr;
    ptr += sizeof(void*) * ndims;

    st->dims = (int*)ptr;
    ptr += sizeof(int) * ndims;

    st->tmpbuf = (kiss_fft_cpx*)ptr;
    ptr += sizeof(kiss_fft_cpx) * dimprod;

    for (i=0;i<ndims;++i) {
        size_t len;
        st->dims[i] = dims[i];
        kiss_fft_alloc (st->dims[i], inverse_fft, NULL, &len);
        st->states[i] = kiss_fft_alloc (st->dims[i], inverse_fft, ptr,&len);
        ptr += len;
    }
    /*
Hi there!

If you're looking at this particular code, it probably means you've got a brain-dead bounds checker 
that thinks the above code overwrites the end of the array.

It doesn't.

-- Mark 

P.S.
The below code might give you some warm fuzzies and help convince you.
       */
    if ( ptr - (char*)st != (int)memneeded ) {
        fprintf(stderr,
                "################################################################################\n"
                "Internal error! Memory allocation miscalculation\n"
                "################################################################################\n"
               );
    }
    return st;
}