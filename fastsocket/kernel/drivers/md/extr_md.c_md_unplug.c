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
struct mddev {TYPE_1__* plug; scalar_t__ queue; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* unplug_fn ) (TYPE_1__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  blk_unplug (scalar_t__) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

void md_unplug(struct mddev *mddev)
{
	if (mddev->queue)
		blk_unplug(mddev->queue);
	if (mddev->plug)
		mddev->plug->unplug_fn(mddev->plug);
}