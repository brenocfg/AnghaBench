#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct qlcnic_adapter {TYPE_2__* npars; TYPE_1__* ahw; } ;
struct __qlcnic_esw_statistics {size_t context_id; void* numbytes; void* local_frames; void* errors; void* dropped_frames; void* broadcast_frames; void* multicast_frames; void* unicast_frames; int /*<<< orphan*/  version; int /*<<< orphan*/  size; } ;
struct TYPE_4__ {size_t const phy_port; int /*<<< orphan*/  pci_func; } ;
struct TYPE_3__ {scalar_t__ op_mode; size_t act_pci_func; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  QLCNIC_ADD_ESW_STATS (void*,void*) ; 
 scalar_t__ QLCNIC_MGMT_FUNC ; 
 void* QLCNIC_STATS_NOT_AVAIL ; 
 int /*<<< orphan*/  memset (struct __qlcnic_esw_statistics*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ qlcnic_get_port_stats (struct qlcnic_adapter*,int /*<<< orphan*/ ,size_t const,struct __qlcnic_esw_statistics*) ; 

int qlcnic_get_eswitch_stats(struct qlcnic_adapter *adapter, const u8 eswitch,
		const u8 rx_tx, struct __qlcnic_esw_statistics *esw_stats) {

	struct __qlcnic_esw_statistics port_stats;
	u8 i;
	int ret = -EIO;

	if (esw_stats == NULL)
		return -ENOMEM;
	if (adapter->ahw->op_mode != QLCNIC_MGMT_FUNC)
		return -EIO;
	if (adapter->npars == NULL)
		return -EIO;

	memset(esw_stats, 0, sizeof(u64));
	esw_stats->unicast_frames = QLCNIC_STATS_NOT_AVAIL;
	esw_stats->multicast_frames = QLCNIC_STATS_NOT_AVAIL;
	esw_stats->broadcast_frames = QLCNIC_STATS_NOT_AVAIL;
	esw_stats->dropped_frames = QLCNIC_STATS_NOT_AVAIL;
	esw_stats->errors = QLCNIC_STATS_NOT_AVAIL;
	esw_stats->local_frames = QLCNIC_STATS_NOT_AVAIL;
	esw_stats->numbytes = QLCNIC_STATS_NOT_AVAIL;
	esw_stats->context_id = eswitch;

	for (i = 0; i < adapter->ahw->act_pci_func; i++) {
		if (adapter->npars[i].phy_port != eswitch)
			continue;

		memset(&port_stats, 0, sizeof(struct __qlcnic_esw_statistics));
		if (qlcnic_get_port_stats(adapter, adapter->npars[i].pci_func,
					  rx_tx, &port_stats))
			continue;

		esw_stats->size = port_stats.size;
		esw_stats->version = port_stats.version;
		QLCNIC_ADD_ESW_STATS(esw_stats->unicast_frames,
						port_stats.unicast_frames);
		QLCNIC_ADD_ESW_STATS(esw_stats->multicast_frames,
						port_stats.multicast_frames);
		QLCNIC_ADD_ESW_STATS(esw_stats->broadcast_frames,
						port_stats.broadcast_frames);
		QLCNIC_ADD_ESW_STATS(esw_stats->dropped_frames,
						port_stats.dropped_frames);
		QLCNIC_ADD_ESW_STATS(esw_stats->errors,
						port_stats.errors);
		QLCNIC_ADD_ESW_STATS(esw_stats->local_frames,
						port_stats.local_frames);
		QLCNIC_ADD_ESW_STATS(esw_stats->numbytes,
						port_stats.numbytes);
		ret = 0;
	}
	return ret;
}