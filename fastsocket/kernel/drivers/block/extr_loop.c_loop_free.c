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
struct loop_device {int /*<<< orphan*/  lo_list; int /*<<< orphan*/  lo_disk; int /*<<< orphan*/  lo_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_cleanup_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct loop_device*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_disk (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void loop_free(struct loop_device *lo)
{
	blk_cleanup_queue(lo->lo_queue);
	put_disk(lo->lo_disk);
	list_del(&lo->lo_list);
	kfree(lo);
}