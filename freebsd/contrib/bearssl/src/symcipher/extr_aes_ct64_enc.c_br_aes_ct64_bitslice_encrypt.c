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
 int /*<<< orphan*/  br_aes_ct64_bitslice_Sbox (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mix_columns (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  shift_rows (int /*<<< orphan*/ *) ; 

void
br_aes_ct64_bitslice_encrypt(unsigned num_rounds,
	const uint64_t *skey, uint64_t *q)
{
	unsigned u;

	add_round_key(q, skey);
	for (u = 1; u < num_rounds; u ++) {
		br_aes_ct64_bitslice_Sbox(q);
		shift_rows(q);
		mix_columns(q);
		add_round_key(q, skey + (u << 3));
	}
	br_aes_ct64_bitslice_Sbox(q);
	shift_rows(q);
	add_round_key(q, skey + (num_rounds << 3));
}