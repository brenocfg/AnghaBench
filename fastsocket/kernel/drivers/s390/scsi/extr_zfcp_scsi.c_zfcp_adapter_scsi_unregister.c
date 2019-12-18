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
struct zfcp_adapter {struct Scsi_Host* scsi_host; } ;
struct Scsi_Host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fc_remove_host (struct Scsi_Host*) ; 
 int /*<<< orphan*/  scsi_host_put (struct Scsi_Host*) ; 
 int /*<<< orphan*/  scsi_remove_host (struct Scsi_Host*) ; 

void zfcp_adapter_scsi_unregister(struct zfcp_adapter *adapter)
{
	struct Scsi_Host *shost;

	shost = adapter->scsi_host;
	if (!shost)
		return;

	fc_remove_host(shost);
	scsi_remove_host(shost);
	scsi_host_put(shost);
	adapter->scsi_host = NULL;
}