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
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
struct uvd {int /*<<< orphan*/  lock; TYPE_2__ vdev; int /*<<< orphan*/  dp; scalar_t__ last_error; scalar_t__ remove_pending; scalar_t__ user; scalar_t__ uvd_used; TYPE_1__* sbuf; } ;
struct usbvideo {char* drvName; struct uvd* cam; } ;
struct TYPE_3__ {int /*<<< orphan*/ * urb; } ;

/* Variables and functions */
 int /*<<< orphan*/  FRAMES_PER_DESC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  RingQueue_Initialize (int /*<<< orphan*/ *) ; 
 int USBVIDEO_NUMSBUF ; 
 int /*<<< orphan*/  dbg (char*,int,struct uvd*) ; 
 int /*<<< orphan*/  err (char*,...) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/ * usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbvideo_ClientDecModCount (struct uvd*) ; 
 int /*<<< orphan*/  usbvideo_ClientIncModCount (struct uvd*) ; 
 int usbvideo_find_struct (struct usbvideo*) ; 
 TYPE_2__ usbvideo_template ; 

struct uvd *usbvideo_AllocateDevice(struct usbvideo *cams)
{
	int i, devnum;
	struct uvd *uvd = NULL;

	if (cams == NULL) {
		err("No usbvideo handle?");
		return NULL;
	}

	devnum = usbvideo_find_struct(cams);
	if (devnum == -1) {
		err("IBM USB camera driver: Too many devices!");
		return NULL;
	}
	uvd = &cams->cam[devnum];
	dbg("Device entry #%d. at $%p", devnum, uvd);

	/* Not relying upon caller we increase module counter ourselves */
	usbvideo_ClientIncModCount(uvd);

	mutex_lock(&uvd->lock);
	for (i=0; i < USBVIDEO_NUMSBUF; i++) {
		uvd->sbuf[i].urb = usb_alloc_urb(FRAMES_PER_DESC, GFP_KERNEL);
		if (uvd->sbuf[i].urb == NULL) {
			err("usb_alloc_urb(%d.) failed.", FRAMES_PER_DESC);
			uvd->uvd_used = 0;
			uvd = NULL;
			goto allocate_done;
		}
	}
	uvd->user=0;
	uvd->remove_pending = 0;
	uvd->last_error = 0;
	RingQueue_Initialize(&uvd->dp);

	/* Initialize video device structure */
	uvd->vdev = usbvideo_template;
	sprintf(uvd->vdev.name, "%.20s USB Camera", cams->drvName);
	/*
	 * The client is free to overwrite those because we
	 * return control to the client's probe function right now.
	 */
allocate_done:
	mutex_unlock(&uvd->lock);
	usbvideo_ClientDecModCount(uvd);
	return uvd;
}