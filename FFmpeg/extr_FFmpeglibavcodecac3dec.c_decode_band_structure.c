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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_assert0 (int) ; 
 int get_bits1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int*,int const*,int) ; 

__attribute__((used)) static void decode_band_structure(GetBitContext *gbc, int blk, int eac3,
                                  int ecpl, int start_subband, int end_subband,
                                  const uint8_t *default_band_struct,
                                  int *num_bands, uint8_t *band_sizes,
                                  uint8_t *band_struct, int band_struct_size)
{
    int subbnd, bnd, n_subbands, n_bands=0;
    uint8_t bnd_sz[22];

    n_subbands = end_subband - start_subband;

    if (!blk)
        memcpy(band_struct, default_band_struct, band_struct_size);

    av_assert0(band_struct_size >= start_subband + n_subbands);

    band_struct += start_subband + 1;

    /* decode band structure from bitstream or use default */
    if (!eac3 || get_bits1(gbc)) {
        for (subbnd = 0; subbnd < n_subbands - 1; subbnd++) {
            band_struct[subbnd] = get_bits1(gbc);
        }
    }

    /* calculate number of bands and band sizes based on band structure.
       note that the first 4 subbands in enhanced coupling span only 6 bins
       instead of 12. */
    if (num_bands || band_sizes ) {
        n_bands = n_subbands;
        bnd_sz[0] = ecpl ? 6 : 12;
        for (bnd = 0, subbnd = 1; subbnd < n_subbands; subbnd++) {
            int subbnd_size = (ecpl && subbnd < 4) ? 6 : 12;
            if (band_struct[subbnd - 1]) {
                n_bands--;
                bnd_sz[bnd] += subbnd_size;
            } else {
                bnd_sz[++bnd] = subbnd_size;
            }
        }
    }

    /* set optional output params */
    if (num_bands)
        *num_bands = n_bands;
    if (band_sizes)
        memcpy(band_sizes, bnd_sz, n_bands);
}