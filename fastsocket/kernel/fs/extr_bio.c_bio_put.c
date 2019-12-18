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
struct bio {int /*<<< orphan*/  (* bi_destructor ) (struct bio*) ;int /*<<< orphan*/ * bi_next; int /*<<< orphan*/  bi_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_BUG_ON (int) ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct bio*) ; 

void bio_put(struct bio *bio)
{
	BIO_BUG_ON(!atomic_read(&bio->bi_cnt));

	/*
	 * last put frees it
	 */
	if (atomic_dec_and_test(&bio->bi_cnt)) {
		bio->bi_next = NULL;
		bio->bi_destructor(bio);
	}
}