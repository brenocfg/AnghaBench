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
typedef  int uint8_t ;
typedef  int uint16_t ;
struct TYPE_3__ {int bypp; scalar_t__* score_tab; } ;
typedef  TYPE_1__ ZmbvEncContext ;

/* Variables and functions */

__attribute__((used)) static inline int block_cmp(ZmbvEncContext *c, uint8_t *src, int stride,
                            uint8_t *src2, int stride2, int bw, int bh,
                            int *xored)
{
    int sum = 0;
    int i, j;
    uint16_t histogram[256] = {0};
    int bw_bytes = bw * c->bypp;

    /* Build frequency histogram of byte values for src[] ^ src2[] */
    for(j = 0; j < bh; j++){
        for(i = 0; i < bw_bytes; i++){
            int t = src[i] ^ src2[i];
            histogram[t]++;
        }
        src += stride;
        src2 += stride2;
    }

    /* If not all the xored values were 0, then the blocks are different */
    *xored = (histogram[0] < bw_bytes * bh);

    /* Exit early if blocks are equal */
    if (!*xored) return 0;

    /* Sum the entropy of all values */
    for(i = 0; i < 256; i++)
        sum += c->score_tab[histogram[i]];

    return sum;
}