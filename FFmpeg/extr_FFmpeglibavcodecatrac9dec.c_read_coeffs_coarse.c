#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct TYPE_8__ {int /*<<< orphan*/  table; } ;
typedef  TYPE_1__ VLC ;
struct TYPE_11__ {int* q_coeffs_coarse; int q_unit_cnt; int* precision_coarse; int* codebookset; } ;
struct TYPE_10__ {int samplerate_idx; TYPE_1__*** coeff_vlc; } ;
struct TYPE_9__ {int const value_cnt_pow; int value_cnt; int const value_bits; int /*<<< orphan*/  max_bit_size; } ;
typedef  TYPE_2__ HuffmanCodebook ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_3__ ATRAC9Context ;
typedef  TYPE_4__ ATRAC9ChannelData ;
typedef  int /*<<< orphan*/  ATRAC9BlockData ;

/* Variables and functions */
 TYPE_2__*** at9_huffman_coeffs ; 
 int* at9_q_unit_to_codebookidx ; 
 int* at9_q_unit_to_coeff_cnt ; 
 size_t* at9_q_unit_to_coeff_idx ; 
 int get_bits (int /*<<< orphan*/ *,int const) ; 
 int get_vlc2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int sign_extend (int,int const) ; 

__attribute__((used)) static inline void read_coeffs_coarse(ATRAC9Context *s, ATRAC9BlockData *b,
                                      ATRAC9ChannelData *c, GetBitContext *gb)
{
    const int max_prec = s->samplerate_idx > 7 ? 1 : 7;

    memset(c->q_coeffs_coarse, 0, sizeof(c->q_coeffs_coarse));

    for (int i = 0; i < c->q_unit_cnt; i++) {
        int *coeffs = &c->q_coeffs_coarse[at9_q_unit_to_coeff_idx[i]];
        const int bands = at9_q_unit_to_coeff_cnt[i];
        const int prec = c->precision_coarse[i] + 1;

        if (prec <= max_prec) {
            const int cb = c->codebookset[i];
            const int cbi = at9_q_unit_to_codebookidx[i];
            const VLC *tab = &s->coeff_vlc[cb][prec][cbi];
            const HuffmanCodebook *huff = &at9_huffman_coeffs[cb][prec][cbi];
            const int groups = bands >> huff->value_cnt_pow;

            for (int j = 0; j < groups; j++) {
                uint16_t val = get_vlc2(gb, tab->table, 9, huff->max_bit_size);

                for (int k = 0; k < huff->value_cnt; k++) {
                    coeffs[k] = sign_extend(val, huff->value_bits);
                    val >>= huff->value_bits;
                }

                coeffs += huff->value_cnt;
            }
        } else {
            for (int j = 0; j < bands; j++)
                coeffs[j] = sign_extend(get_bits(gb, prec), prec);
        }
    }
}