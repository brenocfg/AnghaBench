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
typedef  int mpc_uint32_t ;
typedef  int /*<<< orphan*/  mpc_lut_data ;
typedef  int mpc_int32_t ;
typedef  int mpc_int16_t ;
struct TYPE_6__ {size_t* Res_L; size_t* Res_R; size_t* MS_Flag; int max_band; int* SCFI_L; int* SCFI_R; int** SCF_Index_L; int** SCF_Index_R; TYPE_1__* Q; scalar_t__ ms; } ;
typedef  TYPE_2__ mpc_decoder ;
typedef  int /*<<< orphan*/  mpc_bits_reader ;
struct TYPE_5__ {int* L; int* R; } ;

/* Variables and functions */
 int* Dc ; 
 int* Res_bit ; 
 int /*<<< orphan*/  const mpc_HuffDSCF ; 
 int /*<<< orphan*/  const mpc_HuffHdr ; 
 int /*<<< orphan*/ ** mpc_HuffQ ; 
 void* mpc_bits_huff_dec (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int mpc_bits_huff_lut (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 size_t mpc_bits_read (int /*<<< orphan*/ *,int) ; 
 int mpc_random_int (TYPE_2__*) ; 
 int /*<<< orphan*/  mpc_table_HuffSCFI ; 

void mpc_decoder_read_bitstream_sv7(mpc_decoder * d, mpc_bits_reader * r)
{
    // these arrays hold decoding results for bundled quantizers (3- and 5-step)
    static const mpc_int32_t idx30[] = { -1, 0, 1,-1, 0, 1,-1, 0, 1,-1, 0, 1,-1, 0, 1,-1, 0, 1,-1, 0, 1,-1, 0, 1,-1, 0, 1};
    static const mpc_int32_t idx31[] = { -1,-1,-1, 0, 0, 0, 1, 1, 1,-1,-1,-1, 0, 0, 0, 1, 1, 1,-1,-1,-1, 0, 0, 0, 1, 1, 1};
    static const mpc_int32_t idx32[] = { -1,-1,-1,-1,-1,-1,-1,-1,-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    static const mpc_int32_t idx50[] = { -2,-1, 0, 1, 2,-2,-1, 0, 1, 2,-2,-1, 0, 1, 2,-2,-1, 0, 1, 2,-2,-1, 0, 1, 2};
    static const mpc_int32_t idx51[] = { -2,-2,-2,-2,-2,-1,-1,-1,-1,-1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2};

    mpc_int32_t n, idx, Max_used_Band = 0;

    /***************************** Header *****************************/

    // first subband
	d->Res_L[0] = mpc_bits_read(r, 4);
	d->Res_R[0] = mpc_bits_read(r, 4);
	if (!(d->Res_L[0] == 0 && d->Res_R[0] == 0)) {
		if (d->ms)
        	d->MS_Flag[0] = mpc_bits_read(r, 1);
		Max_used_Band = 1;
	}

    // consecutive subbands
	for ( n = 1; n <= d->max_band; n++ ) {
		idx   = mpc_bits_huff_lut(r, & mpc_HuffHdr);
		d->Res_L[n] = (idx!=4) ? d->Res_L[n - 1] + idx : (int) mpc_bits_read(r, 4);

		idx   = mpc_bits_huff_lut(r, & mpc_HuffHdr);
		d->Res_R[n] = (idx!=4) ? d->Res_R[n - 1] + idx : (int) mpc_bits_read(r, 4);

		if (!(d->Res_L[n] == 0 && d->Res_R[n] == 0)) {
			if (d->ms)
            	d->MS_Flag[n] = mpc_bits_read(r, 1);
			Max_used_Band = n + 1;
		}
    }

    /****************************** SCFI ******************************/
    for ( n = 0; n < Max_used_Band; n++ ) {
		if (d->Res_L[n])
			d->SCFI_L[n] = mpc_bits_huff_dec(r, mpc_table_HuffSCFI);
		if (d->Res_R[n])
			d->SCFI_R[n] = mpc_bits_huff_dec(r, mpc_table_HuffSCFI);
    }

    /**************************** SCF/DSCF ****************************/
    for ( n = 0; n < Max_used_Band; n++ ) {
		mpc_int32_t * SCF = d->SCF_Index_L[n];
		mpc_uint32_t Res  = d->Res_L[n], SCFI = d->SCFI_L[n];
		do {
			if (Res) {
				switch (SCFI) {
					case 1:
						idx  = mpc_bits_huff_lut(r, & mpc_HuffDSCF);
						SCF[0] = (idx!=8) ? SCF[2] + idx : (int) mpc_bits_read(r, 6);
						idx  = mpc_bits_huff_lut(r, & mpc_HuffDSCF);
						SCF[1] = (idx!=8) ? SCF[0] + idx : (int) mpc_bits_read(r, 6);
						SCF[2] = SCF[1];
						break;
					case 3:
						idx  = mpc_bits_huff_lut(r, & mpc_HuffDSCF);
						SCF[0] = (idx!=8) ? SCF[2] + idx : (int) mpc_bits_read(r, 6);
						SCF[1] = SCF[0];
						SCF[2] = SCF[1];
						break;
					case 2:
						idx  = mpc_bits_huff_lut(r, & mpc_HuffDSCF);
						SCF[0] = (idx!=8) ? SCF[2] + idx : (int) mpc_bits_read(r, 6);
						SCF[1] = SCF[0];
						idx  = mpc_bits_huff_lut(r, & mpc_HuffDSCF);
						SCF[2] = (idx!=8) ? SCF[1] + idx : (int) mpc_bits_read(r, 6);
						break;
					case 0:
						idx  = mpc_bits_huff_lut(r, & mpc_HuffDSCF);
						SCF[0] = (idx!=8) ? SCF[2] + idx : (int) mpc_bits_read(r, 6);
						idx  = mpc_bits_huff_lut(r, & mpc_HuffDSCF);
						SCF[1] = (idx!=8) ? SCF[0] + idx : (int) mpc_bits_read(r, 6);
						idx  = mpc_bits_huff_lut(r, & mpc_HuffDSCF);
						SCF[2] = (idx!=8) ? SCF[1] + idx : (int) mpc_bits_read(r, 6);
						break;
					default:
						return;
				}
				if (SCF[0] > 1024)
					SCF[0] = 0x8080;
				if (SCF[1] > 1024)
					SCF[1] = 0x8080;
				if (SCF[2] > 1024)
					SCF[2] = 0x8080;
			}
			Res = d->Res_R[n];
			SCFI = d->SCFI_R[n];
		} while ( SCF == d->SCF_Index_L[n] && (SCF = d->SCF_Index_R[n]));
    }

//     if (d->seeking == TRUE)
//         return;

    /***************************** Samples ****************************/
    for ( n = 0; n < Max_used_Band; n++ ) {
		mpc_int16_t *q = d->Q[n].L, Res = d->Res_L[n];
		do {
			mpc_int32_t k;
			const mpc_lut_data *Table;
			switch (Res) {
				case  -2: case  -3: case  -4: case  -5: case  -6: case  -7: case  -8: case  -9:
				case -10: case -11: case -12: case -13: case -14: case -15: case -16: case -17: case 0:
					break;
				case -1:
					for (k=0; k<36; k++ ) {
						mpc_uint32_t tmp = mpc_random_int(d);
						q[k] = ((tmp >> 24) & 0xFF) + ((tmp >> 16) & 0xFF) + ((tmp >>  8) & 0xFF) + ((tmp >>  0) & 0xFF) - 510;
					}
					break;
				case 1:
					Table = & mpc_HuffQ[0][mpc_bits_read(r, 1)];
					for ( k = 0; k < 36; k += 3) {
						idx = mpc_bits_huff_lut(r, Table);
						q[k] = idx30[idx];
						q[k + 1] = idx31[idx];
						q[k + 2] = idx32[idx];
					}
					break;
				case 2:
					Table = & mpc_HuffQ[1][mpc_bits_read(r, 1)];
					for ( k = 0; k < 36; k += 2) {
						idx = mpc_bits_huff_lut(r, Table);
						q[k] = idx50[idx];
						q[k + 1] = idx51[idx];
					}
					break;
				case 3:
				case 4:
				case 5:
				case 6:
				case 7:
					Table = & mpc_HuffQ[Res - 1][mpc_bits_read(r, 1)];
					for ( k = 0; k < 36; k++ )
						q[k] = mpc_bits_huff_lut(r, Table);
					break;
				case 8: case 9: case 10: case 11: case 12: case 13: case 14: case 15: case 16: case 17:
					for ( k = 0; k < 36; k++ )
						q[k] = (mpc_int32_t)mpc_bits_read(r, Res_bit[Res]) - Dc[Res];
					break;
				default:
					return;
			}

			Res = d->Res_R[n];
		} while (q == d->Q[n].L && (q = d->Q[n].R));
    }
}