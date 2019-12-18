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
struct thin_c {int /*<<< orphan*/  td; } ;
struct bio {int bi_rw; } ;

/* Variables and functions */
 int BIO_FLUSH ; 
 int BIO_FUA ; 
 scalar_t__ dm_thin_changed_this_transaction (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bio_triggers_commit(struct thin_c *tc, struct bio *bio)
{
	return (bio->bi_rw & (BIO_FLUSH | BIO_FUA)) &&
		dm_thin_changed_this_transaction(tc->td);
}