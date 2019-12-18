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
struct strcop_crypto_op {size_t cipher_start; size_t cipher_len; size_t digest_start; size_t digest_len; size_t csum_start; size_t csum_len; scalar_t__ do_csum; scalar_t__ do_digest; scalar_t__ do_cipher; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG (int /*<<< orphan*/ ) ; 
 size_t INT_MAX ; 
 int /*<<< orphan*/  printk (char*,size_t,size_t) ; 

__attribute__((used)) static size_t next_cfg_change_ix(struct strcop_crypto_op *crp_op, size_t ix)
{
	size_t ch_ix = INT_MAX;
	size_t tmp_ix = 0;

	if (crp_op->do_cipher && ((crp_op->cipher_start + crp_op->cipher_len) > ix)){
		if (crp_op->cipher_start > ix) {
			ch_ix = crp_op->cipher_start;
		} else {
			ch_ix = crp_op->cipher_start + crp_op->cipher_len;
		}
	}
	if (crp_op->do_digest && ((crp_op->digest_start + crp_op->digest_len) > ix)){
		if (crp_op->digest_start > ix) {
			tmp_ix = crp_op->digest_start;
		} else {
			tmp_ix = crp_op->digest_start + crp_op->digest_len;
		}
		if (tmp_ix < ch_ix) ch_ix = tmp_ix;
	}
	if (crp_op->do_csum && ((crp_op->csum_start + crp_op->csum_len) > ix)){
		if (crp_op->csum_start > ix) {
			tmp_ix = crp_op->csum_start;
		} else {
			tmp_ix = crp_op->csum_start + crp_op->csum_len;
		}
		if (tmp_ix < ch_ix) ch_ix = tmp_ix;
	}
	if (ch_ix == INT_MAX) ch_ix = ix;
	DEBUG(printk("next_cfg_change_ix prev ix=%d, next ix=%d\n", ix, ch_ix));
	return ch_ix;
}