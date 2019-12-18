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
struct request {struct request* special; } ;
struct mapped_device {int /*<<< orphan*/ * pending; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blk_start_request (struct request*) ; 
 int /*<<< orphan*/  dm_get (struct mapped_device*) ; 
 size_t rq_data_dir (struct request*) ; 

__attribute__((used)) static struct request *dm_start_request(struct mapped_device *md, struct request *orig)
{
	struct request *clone;

	blk_start_request(orig);
	clone = orig->special;
	atomic_inc(&md->pending[rq_data_dir(clone)]);

	/*
	 * Hold the md reference here for the in-flight I/O.
	 * We can't rely on the reference count by device opener,
	 * because the device may be closed during the request completion
	 * when all bios are completed.
	 * See the comment in rq_completed() too.
	 */
	dm_get(md);

	return clone;
}