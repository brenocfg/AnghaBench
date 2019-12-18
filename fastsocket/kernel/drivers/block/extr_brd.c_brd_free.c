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
struct brd_device {int /*<<< orphan*/  brd_queue; int /*<<< orphan*/  brd_disk; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_cleanup_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brd_free_pages (struct brd_device*) ; 
 int /*<<< orphan*/  kfree (struct brd_device*) ; 
 int /*<<< orphan*/  put_disk (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void brd_free(struct brd_device *brd)
{
	put_disk(brd->brd_disk);
	blk_cleanup_queue(brd->brd_queue);
	brd_free_pages(brd);
	kfree(brd);
}