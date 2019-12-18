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
struct backing_dev_info {int dummy; } ;
struct TYPE_2__ {int flags; struct backing_dev_info* backing_dev_info; } ;

/* Variables and functions */
 int PF_SWAPWRITE ; 
 int /*<<< orphan*/  bdi_write_congested (struct backing_dev_info*) ; 
 TYPE_1__* current ; 

__attribute__((used)) static int may_write_to_queue(struct backing_dev_info *bdi)
{
	if (current->flags & PF_SWAPWRITE)
		return 1;
	if (!bdi_write_congested(bdi))
		return 1;
	if (bdi == current->backing_dev_info)
		return 1;
	return 0;
}