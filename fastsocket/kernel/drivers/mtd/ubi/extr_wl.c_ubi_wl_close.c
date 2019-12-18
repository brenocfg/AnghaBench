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
struct ubi_device {int /*<<< orphan*/  lookuptbl; int /*<<< orphan*/  scrub; int /*<<< orphan*/  free; int /*<<< orphan*/  erroneous; int /*<<< orphan*/  used; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_pending (struct ubi_device*) ; 
 int /*<<< orphan*/  dbg_wl (char*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  protection_queue_destroy (struct ubi_device*) ; 
 int /*<<< orphan*/  tree_destroy (int /*<<< orphan*/ *) ; 

void ubi_wl_close(struct ubi_device *ubi)
{
	dbg_wl("close the WL sub-system");
	cancel_pending(ubi);
	protection_queue_destroy(ubi);
	tree_destroy(&ubi->used);
	tree_destroy(&ubi->erroneous);
	tree_destroy(&ubi->free);
	tree_destroy(&ubi->scrub);
	kfree(ubi->lookuptbl);
}