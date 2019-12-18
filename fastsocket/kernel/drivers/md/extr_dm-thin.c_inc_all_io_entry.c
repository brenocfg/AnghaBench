#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pool {int /*<<< orphan*/  all_io_ds; } ;
struct dm_thin_endio_hook {int /*<<< orphan*/  all_io_entry; } ;
struct bio {int bi_rw; } ;
struct TYPE_2__ {struct dm_thin_endio_hook* ptr; } ;

/* Variables and functions */
 int BIO_DISCARD ; 
 int /*<<< orphan*/  dm_deferred_entry_inc (int /*<<< orphan*/ ) ; 
 TYPE_1__* dm_get_mapinfo (struct bio*) ; 

__attribute__((used)) static void inc_all_io_entry(struct pool *pool, struct bio *bio)
{
	struct dm_thin_endio_hook *h;

	if (bio->bi_rw & BIO_DISCARD)
		return;

	h = dm_get_mapinfo(bio)->ptr;
	h->all_io_entry = dm_deferred_entry_inc(pool->all_io_ds);
}