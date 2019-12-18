#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct uea_softc {scalar_t__ dsp_firm; int /*<<< orphan*/  work_q; TYPE_1__* urb_int; int /*<<< orphan*/  kthread; } ;
struct TYPE_3__ {int /*<<< orphan*/  transfer_buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  INS_TO_USBDEV (struct uea_softc*) ; 
 int /*<<< orphan*/  UEA_LOOPBACK_ON ; 
 int /*<<< orphan*/  UEA_SET_MODE ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int kthread_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_firmware (scalar_t__) ; 
 int /*<<< orphan*/  uea_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  uea_enters (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uea_leaves (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uea_request (struct uea_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_free_urb (TYPE_1__*) ; 
 int /*<<< orphan*/  usb_kill_urb (TYPE_1__*) ; 

__attribute__((used)) static void uea_stop(struct uea_softc *sc)
{
	int ret;
	uea_enters(INS_TO_USBDEV(sc));
	ret = kthread_stop(sc->kthread);
	uea_dbg(INS_TO_USBDEV(sc), "kthread finish with status %d\n", ret);

	uea_request(sc, UEA_SET_MODE, UEA_LOOPBACK_ON, 0, NULL);

	usb_kill_urb(sc->urb_int);
	kfree(sc->urb_int->transfer_buffer);
	usb_free_urb(sc->urb_int);

	/* stop any pending boot process, when no one can schedule work */
	destroy_workqueue(sc->work_q);

	if (sc->dsp_firm)
		release_firmware(sc->dsp_firm);
	uea_leaves(INS_TO_USBDEV(sc));
}