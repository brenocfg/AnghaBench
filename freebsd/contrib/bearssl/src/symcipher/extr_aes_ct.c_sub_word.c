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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  br_aes_ct_bitslice_Sbox (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  br_aes_ct_ortho (int /*<<< orphan*/ *) ; 

__attribute__((used)) static uint32_t
sub_word(uint32_t x)
{
	uint32_t q[8];
	int i;

	for (i = 0; i < 8; i ++) {
		q[i] = x;
	}
	br_aes_ct_ortho(q);
	br_aes_ct_bitslice_Sbox(q);
	br_aes_ct_ortho(q);
	return q[0];
}