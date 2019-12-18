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
struct scsi_target {scalar_t__ can_queue; scalar_t__ target_busy; scalar_t__ target_blocked; } ;

/* Variables and functions */

__attribute__((used)) static inline int scsi_target_is_busy(struct scsi_target *starget)
{
	return ((starget->can_queue > 0 &&
		 starget->target_busy >= starget->can_queue) ||
		 starget->target_blocked);
}