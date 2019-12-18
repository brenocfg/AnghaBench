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
struct scrub_dev {int curr; int /*<<< orphan*/  in_flight; struct scrub_bio** bios; } ;
struct scrub_bio {int /*<<< orphan*/  bio; } ;

/* Variables and functions */
 int /*<<< orphan*/  READ ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btrfsic_submit_bio (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void scrub_submit(struct scrub_dev *sdev)
{
	struct scrub_bio *sbio;

	if (sdev->curr == -1)
		return;

	sbio = sdev->bios[sdev->curr];
	sdev->curr = -1;
	atomic_inc(&sdev->in_flight);

	btrfsic_submit_bio(READ, sbio->bio);
}