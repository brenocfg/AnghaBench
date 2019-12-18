#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct uea_softc {scalar_t__ kthread; int /*<<< orphan*/  work_q; int /*<<< orphan*/ * urb_int; TYPE_6__* usb_dev; int /*<<< orphan*/  sync_q; int /*<<< orphan*/  task; int /*<<< orphan*/  send_cmvs; int /*<<< orphan*/  stat; int /*<<< orphan*/  schedule_load_page; int /*<<< orphan*/  dispatch_cmv; } ;
struct intr_pkt {int dummy; } ;
struct TYPE_13__ {TYPE_5__* actconfig; } ;
struct TYPE_12__ {TYPE_4__** interface; } ;
struct TYPE_11__ {TYPE_3__* altsetting; } ;
struct TYPE_10__ {TYPE_2__* endpoint; } ;
struct TYPE_8__ {int /*<<< orphan*/  bInterval; } ;
struct TYPE_9__ {TYPE_1__ desc; } ;

/* Variables and functions */
 scalar_t__ ADI930 ; 
 int E1_INTR_PKT_SIZE ; 
 int E4_INTR_PKT_SIZE ; 
 scalar_t__ EAGLE_IV ; 
 int ENOMEM ; 
 scalar_t__ ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INS_TO_USBDEV (struct uea_softc*) ; 
 scalar_t__ UEA_CHIP_VERSION (struct uea_softc*) ; 
 int /*<<< orphan*/  UEA_INTR_PIPE ; 
 int /*<<< orphan*/  create_workqueue (char*) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct intr_pkt*) ; 
 struct intr_pkt* kmalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ kthread_run (int /*<<< orphan*/ ,struct uea_softc*,char*) ; 
 int /*<<< orphan*/  load_XILINX_firmware (struct uea_softc*) ; 
 int /*<<< orphan*/  uea_dispatch_cmv_e1 ; 
 int /*<<< orphan*/  uea_dispatch_cmv_e4 ; 
 int /*<<< orphan*/  uea_enters (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uea_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  uea_intr ; 
 int /*<<< orphan*/  uea_kthread ; 
 int /*<<< orphan*/  uea_leaves (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uea_load_page_e1 ; 
 int /*<<< orphan*/  uea_load_page_e4 ; 
 int /*<<< orphan*/  uea_schedule_load_page_e1 ; 
 int /*<<< orphan*/  uea_schedule_load_page_e4 ; 
 int /*<<< orphan*/  uea_send_cmvs_e1 ; 
 int /*<<< orphan*/  uea_send_cmvs_e4 ; 
 int /*<<< orphan*/  uea_stat_e1 ; 
 int /*<<< orphan*/  uea_stat_e4 ; 
 int /*<<< orphan*/ * usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_fill_int_urb (int /*<<< orphan*/ *,TYPE_6__*,int /*<<< orphan*/ ,struct intr_pkt*,int,int /*<<< orphan*/ ,struct uea_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_rcvintpipe (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int usb_submit_urb (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int uea_boot(struct uea_softc *sc)
{
	int ret, size;
	struct intr_pkt *intr;

	uea_enters(INS_TO_USBDEV(sc));

	if (UEA_CHIP_VERSION(sc) == EAGLE_IV) {
		size = E4_INTR_PKT_SIZE;
		sc->dispatch_cmv = uea_dispatch_cmv_e4;
		sc->schedule_load_page = uea_schedule_load_page_e4;
		sc->stat = uea_stat_e4;
		sc->send_cmvs = uea_send_cmvs_e4;
		INIT_WORK(&sc->task, uea_load_page_e4);
	} else {
		size = E1_INTR_PKT_SIZE;
		sc->dispatch_cmv = uea_dispatch_cmv_e1;
		sc->schedule_load_page = uea_schedule_load_page_e1;
		sc->stat = uea_stat_e1;
		sc->send_cmvs = uea_send_cmvs_e1;
		INIT_WORK(&sc->task, uea_load_page_e1);
	}

	init_waitqueue_head(&sc->sync_q);

	sc->work_q = create_workqueue("ueagle-dsp");
	if (!sc->work_q) {
		uea_err(INS_TO_USBDEV(sc), "cannot allocate workqueue\n");
		uea_leaves(INS_TO_USBDEV(sc));
		return -ENOMEM;
	}

	if (UEA_CHIP_VERSION(sc) == ADI930)
		load_XILINX_firmware(sc);

	intr = kmalloc(size, GFP_KERNEL);
	if (!intr) {
		uea_err(INS_TO_USBDEV(sc),
		       "cannot allocate interrupt package\n");
		goto err0;
	}

	sc->urb_int = usb_alloc_urb(0, GFP_KERNEL);
	if (!sc->urb_int) {
		uea_err(INS_TO_USBDEV(sc), "cannot allocate interrupt URB\n");
		goto err1;
	}

	usb_fill_int_urb(sc->urb_int, sc->usb_dev,
			 usb_rcvintpipe(sc->usb_dev, UEA_INTR_PIPE),
			 intr, size, uea_intr, sc,
			 sc->usb_dev->actconfig->interface[0]->altsetting[0].
			 endpoint[0].desc.bInterval);

	ret = usb_submit_urb(sc->urb_int, GFP_KERNEL);
	if (ret < 0) {
		uea_err(INS_TO_USBDEV(sc),
		       "urb submition failed with error %d\n", ret);
		goto err1;
	}

	sc->kthread = kthread_run(uea_kthread, sc, "ueagle-atm");
	if (sc->kthread == ERR_PTR(-ENOMEM)) {
		uea_err(INS_TO_USBDEV(sc), "failed to create thread\n");
		goto err2;
	}

	uea_leaves(INS_TO_USBDEV(sc));
	return 0;

err2:
	usb_kill_urb(sc->urb_int);
err1:
	usb_free_urb(sc->urb_int);
	sc->urb_int = NULL;
	kfree(intr);
err0:
	destroy_workqueue(sc->work_q);
	uea_leaves(INS_TO_USBDEV(sc));
	return -ENOMEM;
}