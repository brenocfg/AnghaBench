#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct latency_cont {int /*<<< orphan*/  counter; int /*<<< orphan*/  fabric; int /*<<< orphan*/  channel; } ;
struct TYPE_12__ {int /*<<< orphan*/  lock; struct latency_cont cmd; struct latency_cont write; struct latency_cont read; } ;
struct zfcp_unit {TYPE_6__ latencies; } ;
struct zfcp_fsf_req {TYPE_5__* qtcb; struct zfcp_unit* unit; } ;
struct fsf_qual_latency_info {int /*<<< orphan*/  fabric_lat; int /*<<< orphan*/  channel_lat; } ;
struct TYPE_9__ {int data_direction; } ;
struct TYPE_10__ {TYPE_3__ io; } ;
struct TYPE_7__ {struct fsf_qual_latency_info latency_info; } ;
struct TYPE_8__ {TYPE_1__ prot_status_qual; } ;
struct TYPE_11__ {TYPE_4__ bottom; TYPE_2__ prefix; } ;

/* Variables and functions */
#define  FSF_DATADIR_CMND 134 
#define  FSF_DATADIR_DIF_READ_CONVERT 133 
#define  FSF_DATADIR_DIF_READ_STRIP 132 
#define  FSF_DATADIR_DIF_WRITE_CONVERT 131 
#define  FSF_DATADIR_DIF_WRITE_INSERT 130 
#define  FSF_DATADIR_READ 129 
#define  FSF_DATADIR_WRITE 128 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfcp_fsf_update_lat (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void zfcp_fsf_req_latency(struct zfcp_fsf_req *req)
{
	struct fsf_qual_latency_info *lat_inf;
	struct latency_cont *lat;
	struct zfcp_unit *unit = req->unit;

	lat_inf = &req->qtcb->prefix.prot_status_qual.latency_info;

	switch (req->qtcb->bottom.io.data_direction) {
	case FSF_DATADIR_DIF_READ_STRIP:
	case FSF_DATADIR_DIF_READ_CONVERT:
	case FSF_DATADIR_READ:
		lat = &unit->latencies.read;
		break;
	case FSF_DATADIR_DIF_WRITE_INSERT:
	case FSF_DATADIR_DIF_WRITE_CONVERT:
	case FSF_DATADIR_WRITE:
		lat = &unit->latencies.write;
		break;
	case FSF_DATADIR_CMND:
		lat = &unit->latencies.cmd;
		break;
	default:
		return;
	}

	spin_lock(&unit->latencies.lock);
	zfcp_fsf_update_lat(&lat->channel, lat_inf->channel_lat);
	zfcp_fsf_update_lat(&lat->fabric, lat_inf->fabric_lat);
	lat->counter++;
	spin_unlock(&unit->latencies.lock);
}