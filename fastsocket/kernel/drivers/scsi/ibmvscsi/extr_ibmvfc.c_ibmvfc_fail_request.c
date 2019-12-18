#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ibmvfc_event {int /*<<< orphan*/  (* done ) (struct ibmvfc_event*) ;int /*<<< orphan*/  timer; int /*<<< orphan*/  queue; TYPE_3__* xfer_iu; TYPE_1__* cmnd; } ;
struct TYPE_5__ {int /*<<< orphan*/  status; } ;
struct TYPE_6__ {TYPE_2__ mad_common; } ;
struct TYPE_4__ {int result; } ;

/* Variables and functions */
 int /*<<< orphan*/  IBMVFC_MAD_DRIVER_FAILED ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ibmvfc_scsi_eh_done (struct ibmvfc_event*) ; 
 int /*<<< orphan*/  ibmvfc_trc_end (struct ibmvfc_event*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct ibmvfc_event*) ; 

__attribute__((used)) static void ibmvfc_fail_request(struct ibmvfc_event *evt, int error_code)
{
	if (evt->cmnd) {
		evt->cmnd->result = (error_code << 16);
		evt->done = ibmvfc_scsi_eh_done;
	} else
		evt->xfer_iu->mad_common.status = IBMVFC_MAD_DRIVER_FAILED;

	list_del(&evt->queue);
	del_timer(&evt->timer);
	ibmvfc_trc_end(evt);
	evt->done(evt);
}