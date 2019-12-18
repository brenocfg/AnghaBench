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
struct switch_request {int /*<<< orphan*/  wait; struct file* file; } ;
struct loop_device {int /*<<< orphan*/  lo_queue; } ;
struct file {int dummy; } ;
struct bio {int /*<<< orphan*/ * bi_bdev; struct switch_request* bi_private; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct bio* bio_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  loop_make_request (int /*<<< orphan*/ ,struct bio*) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int loop_switch(struct loop_device *lo, struct file *file)
{
	struct switch_request w;
	struct bio *bio = bio_alloc(GFP_KERNEL, 0);
	if (!bio)
		return -ENOMEM;
	init_completion(&w.wait);
	w.file = file;
	bio->bi_private = &w;
	bio->bi_bdev = NULL;
	loop_make_request(lo->lo_queue, bio);
	wait_for_completion(&w.wait);
	return 0;
}