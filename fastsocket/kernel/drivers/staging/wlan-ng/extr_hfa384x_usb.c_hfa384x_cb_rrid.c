#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  rridresult ;
struct TYPE_10__ {int /*<<< orphan*/  rridresp; } ;
struct TYPE_11__ {int /*<<< orphan*/  rid; } ;
struct TYPE_12__ {TYPE_2__ rridreq; } ;
struct TYPE_13__ {scalar_t__ state; int /*<<< orphan*/  usercb_data; int /*<<< orphan*/  (* usercb ) (int /*<<< orphan*/ *,TYPE_5__*,int /*<<< orphan*/ ) ;TYPE_1__ inbuf; TYPE_3__ outbuf; } ;
typedef  TYPE_4__ hfa384x_usbctlx_t ;
typedef  int /*<<< orphan*/  hfa384x_t ;
struct TYPE_14__ {int /*<<< orphan*/  rid; } ;
typedef  TYPE_5__ hfa384x_rridresult_t ;

/* Variables and functions */
 scalar_t__ CTLX_COMPLETE ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_5__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbctlx_get_rridresult (int /*<<< orphan*/ *,TYPE_5__*) ; 

__attribute__((used)) static void hfa384x_cb_rrid(hfa384x_t *hw, const hfa384x_usbctlx_t *ctlx)
{
	if (ctlx->usercb != NULL) {
		hfa384x_rridresult_t rridresult;

		if (ctlx->state != CTLX_COMPLETE) {
			memset(&rridresult, 0, sizeof(rridresult));
			rridresult.rid = le16_to_cpu(ctlx->outbuf.rridreq.rid);
		} else {
			usbctlx_get_rridresult(&ctlx->inbuf.rridresp,
					       &rridresult);
		}

		ctlx->usercb(hw, &rridresult, ctlx->usercb_data);
	}
}