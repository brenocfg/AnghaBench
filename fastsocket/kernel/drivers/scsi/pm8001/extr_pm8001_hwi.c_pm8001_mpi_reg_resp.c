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
typedef  size_t u32 ;
struct pm8001_hba_info {struct pm8001_ccb_info* ccb_info; } ;
struct pm8001_device {size_t device_id; int /*<<< orphan*/  dcompletion; } ;
struct pm8001_ccb_info {int ccb_tag; int /*<<< orphan*/ * task; struct pm8001_device* device; } ;
struct dev_reg_resp {int /*<<< orphan*/  device_id; int /*<<< orphan*/  status; int /*<<< orphan*/  tag; } ;

/* Variables and functions */
#define  DEVREG_FAILURE_DEVICE_ALREADY_REGISTERED 135 
#define  DEVREG_FAILURE_DEVICE_TYPE_NOT_VALID 134 
#define  DEVREG_FAILURE_INVALID_PHY_ID 133 
#define  DEVREG_FAILURE_OUT_OF_RESOURCE 132 
#define  DEVREG_FAILURE_PHY_ID_ALREADY_REGISTERED 131 
#define  DEVREG_FAILURE_PORT_ID_OUT_OF_RANGE 130 
#define  DEVREG_FAILURE_PORT_NOT_VALID_STATE 129 
#define  DEVREG_SUCCESS 128 
 int /*<<< orphan*/  PM8001_MSG_DBG (struct pm8001_hba_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ ) ; 
 size_t le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm8001_ccb_free (struct pm8001_hba_info*,size_t) ; 
 int /*<<< orphan*/  pm8001_printk (char*,...) ; 

int pm8001_mpi_reg_resp(struct pm8001_hba_info *pm8001_ha, void *piomb)
{
	u32 status;
	u32 device_id;
	u32 htag;
	struct pm8001_ccb_info *ccb;
	struct pm8001_device *pm8001_dev;
	struct dev_reg_resp *registerRespPayload =
		(struct dev_reg_resp *)(piomb + 4);

	htag = le32_to_cpu(registerRespPayload->tag);
	ccb = &pm8001_ha->ccb_info[htag];
	pm8001_dev = ccb->device;
	status = le32_to_cpu(registerRespPayload->status);
	device_id = le32_to_cpu(registerRespPayload->device_id);
	PM8001_MSG_DBG(pm8001_ha,
		pm8001_printk(" register device is status = %d\n", status));
	switch (status) {
	case DEVREG_SUCCESS:
		PM8001_MSG_DBG(pm8001_ha, pm8001_printk("DEVREG_SUCCESS\n"));
		pm8001_dev->device_id = device_id;
		break;
	case DEVREG_FAILURE_OUT_OF_RESOURCE:
		PM8001_MSG_DBG(pm8001_ha,
			pm8001_printk("DEVREG_FAILURE_OUT_OF_RESOURCE\n"));
		break;
	case DEVREG_FAILURE_DEVICE_ALREADY_REGISTERED:
		PM8001_MSG_DBG(pm8001_ha,
		   pm8001_printk("DEVREG_FAILURE_DEVICE_ALREADY_REGISTERED\n"));
		break;
	case DEVREG_FAILURE_INVALID_PHY_ID:
		PM8001_MSG_DBG(pm8001_ha,
			pm8001_printk("DEVREG_FAILURE_INVALID_PHY_ID\n"));
		break;
	case DEVREG_FAILURE_PHY_ID_ALREADY_REGISTERED:
		PM8001_MSG_DBG(pm8001_ha,
		   pm8001_printk("DEVREG_FAILURE_PHY_ID_ALREADY_REGISTERED\n"));
		break;
	case DEVREG_FAILURE_PORT_ID_OUT_OF_RANGE:
		PM8001_MSG_DBG(pm8001_ha,
			pm8001_printk("DEVREG_FAILURE_PORT_ID_OUT_OF_RANGE\n"));
		break;
	case DEVREG_FAILURE_PORT_NOT_VALID_STATE:
		PM8001_MSG_DBG(pm8001_ha,
			pm8001_printk("DEVREG_FAILURE_PORT_NOT_VALID_STATE\n"));
		break;
	case DEVREG_FAILURE_DEVICE_TYPE_NOT_VALID:
		PM8001_MSG_DBG(pm8001_ha,
		       pm8001_printk("DEVREG_FAILURE_DEVICE_TYPE_NOT_VALID\n"));
		break;
	default:
		PM8001_MSG_DBG(pm8001_ha,
		 pm8001_printk("DEVREG_FAILURE_DEVICE_TYPE_NOT_UNSORPORTED\n"));
		break;
	}
	complete(pm8001_dev->dcompletion);
	ccb->task = NULL;
	ccb->ccb_tag = 0xFFFFFFFF;
	pm8001_ccb_free(pm8001_ha, htag);
	return 0;
}