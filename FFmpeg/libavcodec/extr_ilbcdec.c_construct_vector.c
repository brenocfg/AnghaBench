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
 int CB_NSTAGES ; 
 unsigned int SPL_MUL_16_16 (int,int) ; 
 int SUBL ; 
 int gain_dequantization (int,int,int) ; 
 int /*<<< orphan*/  get_codebook (int*,int*,int,int,int) ; 

__attribute__((used)) static void construct_vector (
    int16_t *decvector,   /* (o) Decoded vector */
    int16_t *index,       /* (i) Codebook indices */
    int16_t *gain_index,  /* (i) Gain quantization indices */
    int16_t *mem,         /* (i) Buffer for codevector construction */
    int16_t lMem,         /* (i) Length of buffer */
    int16_t veclen)
{
    int16_t gain[CB_NSTAGES];
    int16_t cbvec0[SUBL];
    int16_t cbvec1[SUBL];
    int16_t cbvec2[SUBL];
    unsigned a32;
    int16_t *gainPtr;
    int j;

    /* gain de-quantization */

    gain[0] = gain_dequantization(gain_index[0], 16384, 0);
    gain[1] = gain_dequantization(gain_index[1], gain[0], 1);
    gain[2] = gain_dequantization(gain_index[2], gain[1], 2);

    /* codebook vector construction and construction of total vector */

    /* Stack based */
    get_codebook(cbvec0, mem, index[0], lMem, veclen);
    get_codebook(cbvec1, mem, index[1], lMem, veclen);
    get_codebook(cbvec2, mem, index[2], lMem, veclen);

    gainPtr = &gain[0];
    for (j = 0; j < veclen; j++) {
        a32 = SPL_MUL_16_16(*gainPtr++, cbvec0[j]);
        a32 += SPL_MUL_16_16(*gainPtr++, cbvec1[j]);
        a32 += SPL_MUL_16_16(*gainPtr, cbvec2[j]);
        gainPtr -= 2;
        decvector[j] = (int)(a32 + 8192) >> 14;
    }
}