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
struct cxgbi_device {int /*<<< orphan*/  csk_init_act_open; int /*<<< orphan*/  csk_alloc_cpls; int /*<<< orphan*/  csk_send_rx_credits; int /*<<< orphan*/  csk_send_close_req; int /*<<< orphan*/  csk_send_abort_req; int /*<<< orphan*/  csk_push_tx_frames; int /*<<< orphan*/  csk_release_offload_resources; } ;

/* Variables and functions */
 scalar_t__ CXGB4I_MAX_CONN ; 
 int /*<<< orphan*/  alloc_cpls ; 
 scalar_t__ cxgb4i_max_connect ; 
 int /*<<< orphan*/  cxgb4i_sport_base ; 
 int cxgbi_device_portmap_create (struct cxgbi_device*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  init_act_open ; 
 int /*<<< orphan*/  pr_info (char*,struct cxgbi_device*) ; 
 int /*<<< orphan*/  push_tx_frames ; 
 int /*<<< orphan*/  release_offload_resources ; 
 int /*<<< orphan*/  send_abort_req ; 
 int /*<<< orphan*/  send_close_req ; 
 int /*<<< orphan*/  send_rx_credits ; 

int cxgb4i_ofld_init(struct cxgbi_device *cdev)
{
	int rc;

	if (cxgb4i_max_connect > CXGB4I_MAX_CONN)
		cxgb4i_max_connect = CXGB4I_MAX_CONN;

	rc = cxgbi_device_portmap_create(cdev, cxgb4i_sport_base,
					cxgb4i_max_connect);
	if (rc < 0)
		return rc;

	cdev->csk_release_offload_resources = release_offload_resources;
	cdev->csk_push_tx_frames = push_tx_frames;
	cdev->csk_send_abort_req = send_abort_req;
	cdev->csk_send_close_req = send_close_req;
	cdev->csk_send_rx_credits = send_rx_credits;
	cdev->csk_alloc_cpls = alloc_cpls;
	cdev->csk_init_act_open = init_act_open;

	pr_info("cdev 0x%p, offload up, added.\n", cdev);
	return 0;
}