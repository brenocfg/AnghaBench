#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  usbctlx_rmem_completor_t ;
typedef  int u16 ;
struct TYPE_11__ {int /*<<< orphan*/  rmemresp; } ;
struct TYPE_9__ {void* page; void* offset; void* frmlen; void* type; } ;
struct TYPE_10__ {TYPE_1__ rmemreq; } ;
struct TYPE_12__ {int outbufsize; TYPE_3__ inbuf; void* usercb_data; int /*<<< orphan*/  usercb; int /*<<< orphan*/  cmdcb; scalar_t__ reapable; TYPE_2__ outbuf; } ;
typedef  TYPE_4__ hfa384x_usbctlx_t ;
typedef  int /*<<< orphan*/  hfa384x_t ;
typedef  int /*<<< orphan*/  ctlx_usercb_t ;
typedef  int /*<<< orphan*/  ctlx_cmdcb_t ;
typedef  scalar_t__ CMD_MODE ;

/* Variables and functions */
 scalar_t__ DOWAIT ; 
 int ENOMEM ; 
 int HFA384x_USB_RMEMREQ ; 
 int /*<<< orphan*/  ROUNDUP64 (int) ; 
 void* cpu_to_le16 (int) ; 
 int hfa384x_usbctlx_complete_sync (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int hfa384x_usbctlx_submit (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  init_rmem_completor (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,unsigned int) ; 
 int /*<<< orphan*/  kfree (TYPE_4__*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,...) ; 
 TYPE_4__* usbctlx_alloc () ; 

__attribute__((used)) static int
hfa384x_dormem(hfa384x_t *hw,
	       CMD_MODE mode,
	       u16 page,
	       u16 offset,
	       void *data,
	       unsigned int len,
	       ctlx_cmdcb_t cmdcb, ctlx_usercb_t usercb, void *usercb_data)
{
	int result;
	hfa384x_usbctlx_t *ctlx;

	ctlx = usbctlx_alloc();
	if (ctlx == NULL) {
		result = -ENOMEM;
		goto done;
	}

	/* Initialize the command */
	ctlx->outbuf.rmemreq.type = cpu_to_le16(HFA384x_USB_RMEMREQ);
	ctlx->outbuf.rmemreq.frmlen =
	    cpu_to_le16(sizeof(ctlx->outbuf.rmemreq.offset) +
			sizeof(ctlx->outbuf.rmemreq.page) + len);
	ctlx->outbuf.rmemreq.offset = cpu_to_le16(offset);
	ctlx->outbuf.rmemreq.page = cpu_to_le16(page);

	ctlx->outbufsize = sizeof(ctlx->outbuf.rmemreq);

	pr_debug("type=0x%04x frmlen=%d offset=0x%04x page=0x%04x\n",
		 ctlx->outbuf.rmemreq.type,
		 ctlx->outbuf.rmemreq.frmlen,
		 ctlx->outbuf.rmemreq.offset, ctlx->outbuf.rmemreq.page);

	pr_debug("pktsize=%zd\n", ROUNDUP64(sizeof(ctlx->outbuf.rmemreq)));

	ctlx->reapable = mode;
	ctlx->cmdcb = cmdcb;
	ctlx->usercb = usercb;
	ctlx->usercb_data = usercb_data;

	result = hfa384x_usbctlx_submit(hw, ctlx);
	if (result != 0) {
		kfree(ctlx);
	} else if (mode == DOWAIT) {
		usbctlx_rmem_completor_t completor;

		result =
		    hfa384x_usbctlx_complete_sync(hw, ctlx,
						  init_rmem_completor
						  (&completor,
						   &ctlx->inbuf.rmemresp, data,
						   len));
	}

done:
	return result;
}