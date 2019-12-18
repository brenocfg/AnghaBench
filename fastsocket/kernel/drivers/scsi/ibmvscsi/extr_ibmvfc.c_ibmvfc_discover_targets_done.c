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
typedef  int u32 ;
struct ibmvfc_host {int /*<<< orphan*/  work_wait_q; int /*<<< orphan*/  dev; int /*<<< orphan*/  num_targets; } ;
struct ibmvfc_event {TYPE_1__* xfer_iu; struct ibmvfc_host* vhost; } ;
struct TYPE_4__ {int status; } ;
struct ibmvfc_discover_targets {int /*<<< orphan*/  error; int /*<<< orphan*/  status; int /*<<< orphan*/  num_written; TYPE_2__ common; } ;
struct TYPE_3__ {struct ibmvfc_discover_targets discover_targets; } ;

/* Variables and functions */
 int IBMVFC_DEFAULT_LOG_LEVEL ; 
 int /*<<< orphan*/  IBMVFC_HOST_ACTION_ALLOC_TGTS ; 
 int /*<<< orphan*/  IBMVFC_LINK_DEAD ; 
#define  IBMVFC_MAD_DRIVER_FAILED 130 
#define  IBMVFC_MAD_FAILED 129 
#define  IBMVFC_MAD_SUCCESS 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ibmvfc_dbg (struct ibmvfc_host*,char*) ; 
 int /*<<< orphan*/  ibmvfc_free_event (struct ibmvfc_event*) ; 
 int /*<<< orphan*/  ibmvfc_get_cmd_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibmvfc_link_down (struct ibmvfc_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibmvfc_log (struct ibmvfc_host*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ibmvfc_retry_host_init (struct ibmvfc_host*) ; 
 int /*<<< orphan*/  ibmvfc_set_host_action (struct ibmvfc_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ibmvfc_discover_targets_done(struct ibmvfc_event *evt)
{
	struct ibmvfc_host *vhost = evt->vhost;
	struct ibmvfc_discover_targets *rsp = &evt->xfer_iu->discover_targets;
	u32 mad_status = rsp->common.status;
	int level = IBMVFC_DEFAULT_LOG_LEVEL;

	switch (mad_status) {
	case IBMVFC_MAD_SUCCESS:
		ibmvfc_dbg(vhost, "Discover Targets succeeded\n");
		vhost->num_targets = rsp->num_written;
		ibmvfc_set_host_action(vhost, IBMVFC_HOST_ACTION_ALLOC_TGTS);
		break;
	case IBMVFC_MAD_FAILED:
		level += ibmvfc_retry_host_init(vhost);
		ibmvfc_log(vhost, level, "Discover Targets failed: %s (%x:%x)\n",
			   ibmvfc_get_cmd_error(rsp->status, rsp->error), rsp->status, rsp->error);
		break;
	case IBMVFC_MAD_DRIVER_FAILED:
		break;
	default:
		dev_err(vhost->dev, "Invalid Discover Targets response: 0x%x\n", mad_status);
		ibmvfc_link_down(vhost, IBMVFC_LINK_DEAD);
		break;
	}

	ibmvfc_free_event(evt);
	wake_up(&vhost->work_wait_q);
}