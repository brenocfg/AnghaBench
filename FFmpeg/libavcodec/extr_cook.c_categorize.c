#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int samples_per_channel; int /*<<< orphan*/  gb; } ;
struct TYPE_5__ {int numvector_size; int bits_per_subpacket; int total_subbands; } ;
typedef  TYPE_1__ COOKSubpacket ;
typedef  TYPE_2__ COOKContext ;

/* Variables and functions */
 int av_clip_uintp2 (int,int) ; 
 scalar_t__* expbits_tab ; 
 int get_bits_count (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void categorize(COOKContext *q, COOKSubpacket *p, const int *quant_index_table,
                       int *category, int *category_index)
{
    int exp_idx, bias, tmpbias1, tmpbias2, bits_left, num_bits, index, v, i, j;
    int exp_index2[102] = { 0 };
    int exp_index1[102] = { 0 };

    int tmp_categorize_array[128 * 2] = { 0 };
    int tmp_categorize_array1_idx = p->numvector_size;
    int tmp_categorize_array2_idx = p->numvector_size;

    bits_left = p->bits_per_subpacket - get_bits_count(&q->gb);

    if (bits_left > q->samples_per_channel)
        bits_left = q->samples_per_channel +
                    ((bits_left - q->samples_per_channel) * 5) / 8;

    bias = -32;

    /* Estimate bias. */
    for (i = 32; i > 0; i = i / 2) {
        num_bits = 0;
        index    = 0;
        for (j = p->total_subbands; j > 0; j--) {
            exp_idx = av_clip_uintp2((i - quant_index_table[index] + bias) / 2, 3);
            index++;
            num_bits += expbits_tab[exp_idx];
        }
        if (num_bits >= bits_left - 32)
            bias += i;
    }

    /* Calculate total number of bits. */
    num_bits = 0;
    for (i = 0; i < p->total_subbands; i++) {
        exp_idx = av_clip_uintp2((bias - quant_index_table[i]) / 2, 3);
        num_bits += expbits_tab[exp_idx];
        exp_index1[i] = exp_idx;
        exp_index2[i] = exp_idx;
    }
    tmpbias1 = tmpbias2 = num_bits;

    for (j = 1; j < p->numvector_size; j++) {
        if (tmpbias1 + tmpbias2 > 2 * bits_left) {  /* ---> */
            int max = -999999;
            index = -1;
            for (i = 0; i < p->total_subbands; i++) {
                if (exp_index1[i] < 7) {
                    v = (-2 * exp_index1[i]) - quant_index_table[i] + bias;
                    if (v >= max) {
                        max   = v;
                        index = i;
                    }
                }
            }
            if (index == -1)
                break;
            tmp_categorize_array[tmp_categorize_array1_idx++] = index;
            tmpbias1 -= expbits_tab[exp_index1[index]] -
                        expbits_tab[exp_index1[index] + 1];
            ++exp_index1[index];
        } else {  /* <--- */
            int min = 999999;
            index = -1;
            for (i = 0; i < p->total_subbands; i++) {
                if (exp_index2[i] > 0) {
                    v = (-2 * exp_index2[i]) - quant_index_table[i] + bias;
                    if (v < min) {
                        min   = v;
                        index = i;
                    }
                }
            }
            if (index == -1)
                break;
            tmp_categorize_array[--tmp_categorize_array2_idx] = index;
            tmpbias2 -= expbits_tab[exp_index2[index]] -
                        expbits_tab[exp_index2[index] - 1];
            --exp_index2[index];
        }
    }

    for (i = 0; i < p->total_subbands; i++)
        category[i] = exp_index2[i];

    for (i = 0; i < p->numvector_size - 1; i++)
        category_index[i] = tmp_categorize_array[tmp_categorize_array2_idx++];
}