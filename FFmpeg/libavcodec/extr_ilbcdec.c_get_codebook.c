#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int int16_t ;

/* Variables and functions */
 int CB_FILTERLEN ; 
 int CB_HALFFILTERLEN ; 
 scalar_t__ SPL_MUL_16_16 (int,int) ; 
 int SUBL ; 
 int /*<<< orphan*/  create_augmented_vector (int,int*,int*) ; 
 int /*<<< orphan*/  filter_mafq12 (int*,int*,int*,int,int) ; 
 scalar_t__ kCbFiltersRev ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void get_codebook(int16_t * cbvec,   /* (o) Constructed codebook vector */
                     int16_t * mem,     /* (i) Codebook buffer */
                     int16_t index,     /* (i) Codebook index */
                     int16_t lMem,      /* (i) Length of codebook buffer */
                     int16_t cbveclen   /* (i) Codebook vector length */
)
{
    int16_t k, base_size;
    int16_t lag;
    /* Stack based */
    int16_t tempbuff2[SUBL + 5];

    /* Determine size of codebook sections */
    base_size = lMem - cbveclen + 1;

    if (cbveclen == SUBL) {
        base_size += cbveclen / 2;
    }

    /* No filter -> First codebook section */
    if (index < lMem - cbveclen + 1) {
        /* first non-interpolated vectors */

        k = index + cbveclen;
        /* get vector */
        memcpy(cbvec, mem + lMem - k, cbveclen * 2);
    } else if (index < base_size) {

        /* Calculate lag */

        k = (int16_t) SPL_MUL_16_16(2, (index - (lMem - cbveclen + 1))) + cbveclen;

        lag = k / 2;

        create_augmented_vector(lag, mem + lMem, cbvec);
    } else {
        int16_t memIndTest;

        /* first non-interpolated vectors */

        if (index - base_size < lMem - cbveclen + 1) {

            /* Set up filter memory, stuff zeros outside memory buffer */

            memIndTest = lMem - (index - base_size + cbveclen);

            memset(mem - CB_HALFFILTERLEN, 0, CB_HALFFILTERLEN * 2);
            memset(mem + lMem, 0, CB_HALFFILTERLEN * 2);

            /* do filtering to get the codebook vector */

            filter_mafq12(&mem[memIndTest + 4], cbvec, (int16_t *) kCbFiltersRev, CB_FILTERLEN, cbveclen);
        } else {
            /* interpolated vectors */
            /* Stuff zeros outside memory buffer  */
            memIndTest = lMem - cbveclen - CB_FILTERLEN;
            memset(mem + lMem, 0, CB_HALFFILTERLEN * 2);

            /* do filtering */
            filter_mafq12(&mem[memIndTest + 7], tempbuff2, (int16_t *) kCbFiltersRev, CB_FILTERLEN, (int16_t) (cbveclen + 5));

            /* Calculate lag index */
            lag = (cbveclen << 1) - 20 + index - base_size - lMem - 1;

            create_augmented_vector(lag, tempbuff2 + SUBL + 5, cbvec);
        }
    }
}