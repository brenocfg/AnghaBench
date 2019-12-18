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
struct strcop_crypto_op {size_t cipher_start; size_t digest_start; size_t csum_start; scalar_t__ do_csum; scalar_t__ do_digest; scalar_t__ do_cipher; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*,size_t) ; 

__attribute__((used)) static size_t first_cfg_change_ix(struct strcop_crypto_op *crp_op)
{
	size_t ch_ix = 0;

	if (crp_op->do_cipher) ch_ix = crp_op->cipher_start;
	if (crp_op->do_digest && (crp_op->digest_start < ch_ix)) ch_ix = crp_op->digest_start;
	if (crp_op->do_csum && (crp_op->csum_start < ch_ix)) ch_ix = crp_op->csum_start;

	DEBUG(printk("first_cfg_change_ix: ix=%d\n", ch_ix));
	return ch_ix;
}