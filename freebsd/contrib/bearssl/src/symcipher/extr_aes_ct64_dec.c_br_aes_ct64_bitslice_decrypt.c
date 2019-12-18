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
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  add_round_key (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  br_aes_ct64_bitslice_invSbox (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  inv_mix_columns (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  inv_shift_rows (int /*<<< orphan*/ *) ; 

void
br_aes_ct64_bitslice_decrypt(unsigned num_rounds,
	const uint64_t *skey, uint64_t *q)
{
	unsigned u;

	add_round_key(q, skey + (num_rounds << 3));
	for (u = num_rounds - 1; u > 0; u --) {
		inv_shift_rows(q);
		br_aes_ct64_bitslice_invSbox(q);
		add_round_key(q, skey + (u << 3));
		inv_mix_columns(q);
	}
	inv_shift_rows(q);
	br_aes_ct64_bitslice_invSbox(q);
	add_round_key(q, skey);
}