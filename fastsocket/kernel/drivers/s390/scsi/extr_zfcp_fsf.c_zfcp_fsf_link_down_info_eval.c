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
struct zfcp_fsf_req {struct zfcp_adapter* adapter; } ;
struct zfcp_adapter {TYPE_1__* ccw_device; int /*<<< orphan*/  status; } ;
struct fsf_link_down_info {int error_code; } ;
struct TYPE_4__ {int /*<<< orphan*/  config_lock; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  FSF_PSQ_LINK_FABRIC_LOGIN_UNABLE 139 
#define  FSF_PSQ_LINK_FIRMWARE_UPDATE 138 
#define  FSF_PSQ_LINK_INVALID_WWPN 137 
#define  FSF_PSQ_LINK_MODE_TABLE_CURRUPTED 136 
#define  FSF_PSQ_LINK_NO_FABRIC_RESOURCES 135 
#define  FSF_PSQ_LINK_NO_FCP 134 
#define  FSF_PSQ_LINK_NO_FCP_RESOURCES 133 
#define  FSF_PSQ_LINK_NO_LIGHT 132 
#define  FSF_PSQ_LINK_NO_NPIV_SUPPORT 131 
#define  FSF_PSQ_LINK_NO_WWPN_ASSIGNMENT 130 
#define  FSF_PSQ_LINK_WRAP_PLUG 129 
#define  FSF_PSQ_LINK_WWPN_ASSIGNMENT_CORRUPTED 128 
 int ZFCP_STATUS_ADAPTER_LINK_UNPLUGGED ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set_mask (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  read_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  read_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 TYPE_2__ zfcp_data ; 
 int /*<<< orphan*/  zfcp_erp_adapter_failed (struct zfcp_adapter*,char*,struct zfcp_fsf_req*) ; 
 int /*<<< orphan*/  zfcp_scsi_schedule_rports_block (struct zfcp_adapter*) ; 

__attribute__((used)) static void zfcp_fsf_link_down_info_eval(struct zfcp_fsf_req *req, char *id,
					 struct fsf_link_down_info *link_down)
{
	struct zfcp_adapter *adapter = req->adapter;
	unsigned long flags;

	if (atomic_read(&adapter->status) & ZFCP_STATUS_ADAPTER_LINK_UNPLUGGED)
		return;

	atomic_set_mask(ZFCP_STATUS_ADAPTER_LINK_UNPLUGGED, &adapter->status);

	read_lock_irqsave(&zfcp_data.config_lock, flags);
	zfcp_scsi_schedule_rports_block(adapter);
	read_unlock_irqrestore(&zfcp_data.config_lock, flags);

	if (!link_down)
		goto out;

	switch (link_down->error_code) {
	case FSF_PSQ_LINK_NO_LIGHT:
		dev_warn(&req->adapter->ccw_device->dev,
			 "There is no light signal from the local "
			 "fibre channel cable\n");
		break;
	case FSF_PSQ_LINK_WRAP_PLUG:
		dev_warn(&req->adapter->ccw_device->dev,
			 "There is a wrap plug instead of a fibre "
			 "channel cable\n");
		break;
	case FSF_PSQ_LINK_NO_FCP:
		dev_warn(&req->adapter->ccw_device->dev,
			 "The adjacent fibre channel node does not "
			 "support FCP\n");
		break;
	case FSF_PSQ_LINK_FIRMWARE_UPDATE:
		dev_warn(&req->adapter->ccw_device->dev,
			 "The FCP device is suspended because of a "
			 "firmware update\n");
		break;
	case FSF_PSQ_LINK_INVALID_WWPN:
		dev_warn(&req->adapter->ccw_device->dev,
			 "The FCP device detected a WWPN that is "
			 "duplicate or not valid\n");
		break;
	case FSF_PSQ_LINK_NO_NPIV_SUPPORT:
		dev_warn(&req->adapter->ccw_device->dev,
			 "The fibre channel fabric does not support NPIV\n");
		break;
	case FSF_PSQ_LINK_NO_FCP_RESOURCES:
		dev_warn(&req->adapter->ccw_device->dev,
			 "The FCP adapter cannot support more NPIV ports\n");
		break;
	case FSF_PSQ_LINK_NO_FABRIC_RESOURCES:
		dev_warn(&req->adapter->ccw_device->dev,
			 "The adjacent switch cannot support "
			 "more NPIV ports\n");
		break;
	case FSF_PSQ_LINK_FABRIC_LOGIN_UNABLE:
		dev_warn(&req->adapter->ccw_device->dev,
			 "The FCP adapter could not log in to the "
			 "fibre channel fabric\n");
		break;
	case FSF_PSQ_LINK_WWPN_ASSIGNMENT_CORRUPTED:
		dev_warn(&req->adapter->ccw_device->dev,
			 "The WWPN assignment file on the FCP adapter "
			 "has been damaged\n");
		break;
	case FSF_PSQ_LINK_MODE_TABLE_CURRUPTED:
		dev_warn(&req->adapter->ccw_device->dev,
			 "The mode table on the FCP adapter "
			 "has been damaged\n");
		break;
	case FSF_PSQ_LINK_NO_WWPN_ASSIGNMENT:
		dev_warn(&req->adapter->ccw_device->dev,
			 "All NPIV ports on the FCP adapter have "
			 "been assigned\n");
		break;
	default:
		dev_warn(&req->adapter->ccw_device->dev,
			 "The link between the FCP adapter and "
			 "the FC fabric is down\n");
	}
out:
	zfcp_erp_adapter_failed(adapter, id, req);
}