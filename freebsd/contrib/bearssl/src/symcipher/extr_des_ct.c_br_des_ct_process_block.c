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
 int /*<<< orphan*/  br_dec32be (unsigned char*) ; 
 int /*<<< orphan*/  br_des_do_IP (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  br_des_do_invIP (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  br_enc32be (unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  process_block_unit (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

void
br_des_ct_process_block(unsigned num_rounds,
	const uint32_t *sk_exp, void *block)
{
	unsigned char *buf;
	uint32_t l, r;

	buf = block;
	l = br_dec32be(buf);
	r = br_dec32be(buf + 4);
	br_des_do_IP(&l, &r);
	while (num_rounds -- > 0) {
		process_block_unit(&l, &r, sk_exp);
		sk_exp += 96;
	}
	br_des_do_invIP(&l, &r);
	br_enc32be(buf, l);
	br_enc32be(buf + 4, r);
}