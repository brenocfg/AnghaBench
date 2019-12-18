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
struct zfcp_adapter {scalar_t__ stats_reset; int /*<<< orphan*/  stats_reset_data; int /*<<< orphan*/  qdio; } ;
struct fsf_qtcb_bottom_port {scalar_t__ seconds_since_last_reset; } ;
struct fc_host_statistics {int dummy; } ;
struct Scsi_Host {scalar_t__* hostdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ HZ ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  kfree (struct fsf_qtcb_bottom_port*) ; 
 struct fsf_qtcb_bottom_port* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfcp_adjust_fc_host_stats (struct fc_host_statistics*,struct fsf_qtcb_bottom_port*,int /*<<< orphan*/ ) ; 
 int zfcp_fsf_exchange_port_data_sync (int /*<<< orphan*/ ,struct fsf_qtcb_bottom_port*) ; 
 struct fc_host_statistics* zfcp_init_fc_host_stats (struct zfcp_adapter*) ; 
 int /*<<< orphan*/  zfcp_set_fc_host_stats (struct fc_host_statistics*,struct fsf_qtcb_bottom_port*) ; 

__attribute__((used)) static struct fc_host_statistics *zfcp_get_fc_host_stats(struct Scsi_Host *host)
{
	struct zfcp_adapter *adapter;
	struct fc_host_statistics *fc_stats;
	struct fsf_qtcb_bottom_port *data;
	int ret;

	adapter = (struct zfcp_adapter *)host->hostdata[0];
	fc_stats = zfcp_init_fc_host_stats(adapter);
	if (!fc_stats)
		return NULL;

	data = kzalloc(sizeof(*data), GFP_KERNEL);
	if (!data)
		return NULL;

	ret = zfcp_fsf_exchange_port_data_sync(adapter->qdio, data);
	if (ret) {
		kfree(data);
		return NULL;
	}

	if (adapter->stats_reset &&
	    ((jiffies/HZ - adapter->stats_reset) <
	     data->seconds_since_last_reset))
		zfcp_adjust_fc_host_stats(fc_stats, data,
					  adapter->stats_reset_data);
	else
		zfcp_set_fc_host_stats(fc_stats, data);

	kfree(data);
	return fc_stats;
}