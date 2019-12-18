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
typedef  int u32 ;
struct hwrng {int /*<<< orphan*/  priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  VIA_RNG_CHUNK_1 ; 
 int VIA_XSTORE_CNT_MASK ; 
 int /*<<< orphan*/  udelay (int) ; 
 int xstore (int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int via_rng_data_present(struct hwrng *rng, int wait)
{
	u32 bytes_out;
	u32 *via_rng_datum = (u32 *)(&rng->priv);
	int i;

	/* We choose the recommended 1-byte-per-instruction RNG rate,
	 * for greater randomness at the expense of speed.  Larger
	 * values 2, 4, or 8 bytes-per-instruction yield greater
	 * speed at lesser randomness.
	 *
	 * If you change this to another VIA_CHUNK_n, you must also
	 * change the ->n_bytes values in rng_vendor_ops[] tables.
	 * VIA_CHUNK_8 requires further code changes.
	 *
	 * A copy of MSR_VIA_RNG is placed in eax_out when xstore
	 * completes.
	 */

	for (i = 0; i < 20; i++) {
		*via_rng_datum = 0; /* paranoia, not really necessary */
		bytes_out = xstore(via_rng_datum, VIA_RNG_CHUNK_1);
		bytes_out &= VIA_XSTORE_CNT_MASK;
		if (bytes_out || !wait)
			break;
		udelay(10);
	}
	return bytes_out ? 1 : 0;
}