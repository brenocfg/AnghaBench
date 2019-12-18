#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  bits; int /*<<< orphan*/  table; } ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int* clc_length_tab ; 
 int get_bits (int /*<<< orphan*/ *,int) ; 
 int get_sbits (int /*<<< orphan*/ *,int) ; 
 int get_vlc2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int* mantissa_clc_tab ; 
 int* mantissa_vlc_tab ; 
 TYPE_1__* spectral_coeff_tab ; 

__attribute__((used)) static void read_quant_spectral_coeffs(GetBitContext *gb, int selector,
                                       int coding_flag, int *mantissas,
                                       int num_codes)
{
    int i, code, huff_symb;

    if (selector == 1)
        num_codes /= 2;

    if (coding_flag != 0) {
        /* constant length coding (CLC) */
        int num_bits = clc_length_tab[selector];

        if (selector > 1) {
            for (i = 0; i < num_codes; i++) {
                if (num_bits)
                    code = get_sbits(gb, num_bits);
                else
                    code = 0;
                mantissas[i] = code;
            }
        } else {
            for (i = 0; i < num_codes; i++) {
                if (num_bits)
                    code = get_bits(gb, num_bits); // num_bits is always 4 in this case
                else
                    code = 0;
                mantissas[i * 2    ] = mantissa_clc_tab[code >> 2];
                mantissas[i * 2 + 1] = mantissa_clc_tab[code &  3];
            }
        }
    } else {
        /* variable length coding (VLC) */
        if (selector != 1) {
            for (i = 0; i < num_codes; i++) {
                huff_symb = get_vlc2(gb, spectral_coeff_tab[selector-1].table,
                                     spectral_coeff_tab[selector-1].bits, 3);
                huff_symb += 1;
                code = huff_symb >> 1;
                if (huff_symb & 1)
                    code = -code;
                mantissas[i] = code;
            }
        } else {
            for (i = 0; i < num_codes; i++) {
                huff_symb = get_vlc2(gb, spectral_coeff_tab[selector - 1].table,
                                     spectral_coeff_tab[selector - 1].bits, 3);
                mantissas[i * 2    ] = mantissa_vlc_tab[huff_symb * 2    ];
                mantissas[i * 2 + 1] = mantissa_vlc_tab[huff_symb * 2 + 1];
            }
        }
    }
}