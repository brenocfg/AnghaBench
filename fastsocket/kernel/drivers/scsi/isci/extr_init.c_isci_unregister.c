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
struct isci_host {int /*<<< orphan*/  sas_ha; } ;
struct Scsi_Host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  sas_remove_host (struct Scsi_Host*) ; 
 int /*<<< orphan*/  sas_unregister_ha (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scsi_host_put (struct Scsi_Host*) ; 
 int /*<<< orphan*/  scsi_remove_host (struct Scsi_Host*) ; 
 struct Scsi_Host* to_shost (struct isci_host*) ; 

__attribute__((used)) static void isci_unregister(struct isci_host *isci_host)
{
	struct Scsi_Host *shost;

	if (!isci_host)
		return;

	sas_unregister_ha(&isci_host->sas_ha);

	shost = to_shost(isci_host);
	sas_remove_host(shost);
	scsi_remove_host(shost);
	scsi_host_put(shost);
}