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
struct dst_trans {struct dst_node* n; } ;
struct dst_node {int /*<<< orphan*/  pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_SCHEDULE_TIMEOUT ; 
 int /*<<< orphan*/  dst_trans_crypto_action ; 
 int /*<<< orphan*/  dst_trans_crypto_setup ; 
 int /*<<< orphan*/  dst_trans_put (struct dst_trans*) ; 
 int thread_pool_schedule (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dst_trans*,int /*<<< orphan*/ ) ; 

int dst_trans_crypto(struct dst_trans *t)
{
	struct dst_node *n = t->n;
	int err;

	err = thread_pool_schedule(n->pool,
		dst_trans_crypto_setup, dst_trans_crypto_action,
		t, MAX_SCHEDULE_TIMEOUT);
	if (err)
		goto err_out_exit;

	return 0;

err_out_exit:
	dst_trans_put(t);
	return err;
}