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
typedef  size_t uint8_t ;
typedef  unsigned int int16_t ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  GET_CODE (unsigned int,int,int) ; 
 int* aic_num_band_coeffs ; 
 size_t** aic_scan ; 
 int get_bits (int /*<<< orphan*/ *,int) ; 
 int get_bits1 (int /*<<< orphan*/ *) ; 
 int get_bits_left (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int aic_decode_coeffs(GetBitContext *gb, int16_t *dst,
                             int band, int slice_width, int force_chroma)
{
    int has_skips, coeff_type, coeff_bits, skip_type, skip_bits;
    const int num_coeffs = aic_num_band_coeffs[band];
    const uint8_t *scan = aic_scan[band | force_chroma];
    int mb, idx;
    unsigned val;

    if (get_bits_left(gb) < 5)
        return AVERROR_INVALIDDATA;

    has_skips  = get_bits1(gb);
    coeff_type = get_bits1(gb);
    coeff_bits = get_bits(gb, 3);

    if (has_skips) {
        skip_type = get_bits1(gb);
        skip_bits = get_bits(gb, 3);

        for (mb = 0; mb < slice_width; mb++) {
            idx = -1;
            do {
                GET_CODE(val, skip_type, skip_bits);
                if (val >= 0x10000)
                    return AVERROR_INVALIDDATA;
                idx += val + 1;
                if (idx >= num_coeffs)
                    break;
                GET_CODE(val, coeff_type, coeff_bits);
                val++;
                if (val >= 0x10000)
                    return AVERROR_INVALIDDATA;
                dst[scan[idx]] = val;
            } while (idx < num_coeffs - 1);
            dst += num_coeffs;
        }
    } else {
        for (mb = 0; mb < slice_width; mb++) {
            for (idx = 0; idx < num_coeffs; idx++) {
                GET_CODE(val, coeff_type, coeff_bits);
                if (val >= 0x10000)
                    return AVERROR_INVALIDDATA;
                dst[scan[idx]] = val;
            }
            dst += num_coeffs;
        }
    }
    return 0;
}