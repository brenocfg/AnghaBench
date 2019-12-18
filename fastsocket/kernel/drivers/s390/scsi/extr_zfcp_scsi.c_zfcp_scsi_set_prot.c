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
struct zfcp_adapter {int adapter_features; TYPE_1__* qdio; int /*<<< orphan*/  status; struct Scsi_Host* scsi_host; } ;
struct Scsi_Host {int sg_tablesize; int max_sectors; } ;
struct TYPE_2__ {int max_sbale_per_req; } ;

/* Variables and functions */
 int FSF_FEATURE_DIF_PROT_TYPE1 ; 
 int FSF_FEATURE_DIX_PROT_TCPIP ; 
 unsigned int SHOST_DIF_TYPE1_PROTECTION ; 
 int /*<<< orphan*/  SHOST_DIX_GUARD_IP ; 
 unsigned int SHOST_DIX_TYPE1_PROTECTION ; 
 unsigned int ZFCP_STATUS_ADAPTER_DATA_DIV_ENABLED ; 
 unsigned int atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ enable_dif ; 
 int /*<<< orphan*/  scsi_host_set_guard (struct Scsi_Host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_host_set_prot (struct Scsi_Host*,unsigned int) ; 

void zfcp_scsi_set_prot(struct zfcp_adapter *adapter)
{
	unsigned int mask = 0;
	unsigned int data_div;
	struct Scsi_Host *shost = adapter->scsi_host;

	data_div = atomic_read(&adapter->status) &
		   ZFCP_STATUS_ADAPTER_DATA_DIV_ENABLED;

	if (enable_dif &&
	    adapter->adapter_features & FSF_FEATURE_DIF_PROT_TYPE1)
		mask |= SHOST_DIF_TYPE1_PROTECTION;

#if 0
	if (enable_dif && data_div &&
	    adapter->adapter_features & FSF_FEATURE_DIX_PROT_TCPIP) {
		mask |= SHOST_DIX_TYPE1_PROTECTION;
		scsi_host_set_guard(shost, SHOST_DIX_GUARD_IP);
		shost->sg_tablesize = adapter->qdio->max_sbale_per_req / 2;
		shost->max_sectors = shost->sg_tablesize * 8;
	}
#endif

	scsi_host_set_prot(shost, mask);
}