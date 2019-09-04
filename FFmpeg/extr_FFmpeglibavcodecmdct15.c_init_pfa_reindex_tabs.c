#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int nbits; } ;
struct TYPE_5__ {int* pfa_prereindex; int* pfa_postreindex; TYPE_1__ ptwo_fft; } ;
typedef  TYPE_2__ MDCT15Context ;

/* Variables and functions */
 void* av_malloc_array (int,int) ; 

__attribute__((used)) static inline int init_pfa_reindex_tabs(MDCT15Context *s)
{
    int i, j;
    const int b_ptwo = s->ptwo_fft.nbits; /* Bits for the power of two FFTs */
    const int l_ptwo = 1 << b_ptwo; /* Total length for the power of two FFTs */
    const int inv_1 = l_ptwo << ((4 - b_ptwo) & 3); /* (2^b_ptwo)^-1 mod 15 */
    const int inv_2 = 0xeeeeeeef & ((1U << b_ptwo) - 1); /* 15^-1 mod 2^b_ptwo */

    s->pfa_prereindex = av_malloc_array(15 * l_ptwo, sizeof(*s->pfa_prereindex));
    if (!s->pfa_prereindex)
        return 1;

    s->pfa_postreindex = av_malloc_array(15 * l_ptwo, sizeof(*s->pfa_postreindex));
    if (!s->pfa_postreindex)
        return 1;

    /* Pre/Post-reindex */
    for (i = 0; i < l_ptwo; i++) {
        for (j = 0; j < 15; j++) {
            const int q_pre = ((l_ptwo * j)/15 + i) >> b_ptwo;
            const int q_post = (((j*inv_1)/15) + (i*inv_2)) >> b_ptwo;
            const int k_pre = 15*i + (j - q_pre*15)*(1 << b_ptwo);
            const int k_post = i*inv_2*15 + j*inv_1 - 15*q_post*l_ptwo;
            s->pfa_prereindex[i*15 + j] = k_pre << 1;
            s->pfa_postreindex[k_post] = l_ptwo*j + i;
        }
    }

    return 0;
}