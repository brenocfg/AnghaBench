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
struct dst_node {int /*<<< orphan*/  pool; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_SCHEDULE_TIMEOUT ; 
 int /*<<< orphan*/  bio_put (struct bio*) ; 
 int /*<<< orphan*/  dst_export_crypto_action ; 
 int /*<<< orphan*/  dst_export_crypto_setup ; 
 int thread_pool_schedule (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bio*,int /*<<< orphan*/ ) ; 

int dst_export_crypto(struct dst_node *n, struct bio *bio)
{
	int err;

	err = thread_pool_schedule(n->pool,
		dst_export_crypto_setup, dst_export_crypto_action,
		bio, MAX_SCHEDULE_TIMEOUT);
	if (err)
		goto err_out_exit;

	return 0;

err_out_exit:
	bio_put(bio);
	return err;
}