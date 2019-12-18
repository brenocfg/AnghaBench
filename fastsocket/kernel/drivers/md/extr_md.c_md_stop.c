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
struct mddev {scalar_t__ bio_set; } ;

/* Variables and functions */
 int /*<<< orphan*/  __md_stop (struct mddev*) ; 
 int /*<<< orphan*/  bioset_free (scalar_t__) ; 
 int /*<<< orphan*/  bitmap_destroy (struct mddev*) ; 

void md_stop(struct mddev *mddev)
{
	/* stop the array and free an attached data structures.
	 * This is called from dm-raid
	 */
	__md_stop(mddev);
	bitmap_destroy(mddev);
	if (mddev->bio_set)
		bioset_free(mddev->bio_set);
}