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
struct Scsi_Host {scalar_t__ shost_state; int /*<<< orphan*/  shost_gendev; } ;

/* Variables and functions */
 scalar_t__ SHOST_DEL ; 
 int /*<<< orphan*/  get_device (int /*<<< orphan*/ *) ; 

struct Scsi_Host *scsi_host_get(struct Scsi_Host *shost)
{
	if ((shost->shost_state == SHOST_DEL) ||
		!get_device(&shost->shost_gendev))
		return NULL;
	return shost;
}