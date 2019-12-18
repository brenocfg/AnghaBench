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
struct Scsi_Host {scalar_t__ can_queue; scalar_t__ host_busy; scalar_t__ host_self_blocked; scalar_t__ host_blocked; } ;

/* Variables and functions */

__attribute__((used)) static inline int scsi_host_is_busy(struct Scsi_Host *shost)
{
	if ((shost->can_queue > 0 && shost->host_busy >= shost->can_queue) ||
	    shost->host_blocked || shost->host_self_blocked)
		return 1;

	return 0;
}