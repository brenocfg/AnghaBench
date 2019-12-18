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
struct iscsi_host {int /*<<< orphan*/  initiatorname; int /*<<< orphan*/  hwaddress; int /*<<< orphan*/  netdev; } ;
struct Scsi_Host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_host_put (struct Scsi_Host*) ; 
 struct iscsi_host* shost_priv (struct Scsi_Host*) ; 

void iscsi_host_free(struct Scsi_Host *shost)
{
	struct iscsi_host *ihost = shost_priv(shost);

	kfree(ihost->netdev);
	kfree(ihost->hwaddress);
	kfree(ihost->initiatorname);
	scsi_host_put(shost);
}