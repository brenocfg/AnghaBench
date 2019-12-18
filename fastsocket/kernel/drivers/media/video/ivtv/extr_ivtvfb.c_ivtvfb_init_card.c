#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct osd_info {int dummy; } ;
struct ivtv {int /*<<< orphan*/  ivtvfb_restore; TYPE_1__* osd_info; int /*<<< orphan*/  osd_video_pbase; } ;
struct TYPE_2__ {int /*<<< orphan*/  ivtvfb_info; int /*<<< orphan*/  video_pbase; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FB_BLANK_UNBLANK ; 
 int GFP_ATOMIC ; 
 int /*<<< orphan*/  IVTVFB_ERR (char*,...) ; 
 int __GFP_NOWARN ; 
 int /*<<< orphan*/  ivtv_udma_alloc (struct ivtv*) ; 
 int /*<<< orphan*/  ivtvfb_blank (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ivtvfb_card_id ; 
 int ivtvfb_init_io (struct ivtv*) ; 
 int ivtvfb_init_vidmode (struct ivtv*) ; 
 int /*<<< orphan*/  ivtvfb_release_buffers (struct ivtv*) ; 
 int /*<<< orphan*/  ivtvfb_restore ; 
 int /*<<< orphan*/  ivtvfb_set_par (int /*<<< orphan*/ *) ; 
 TYPE_1__* kzalloc (int,int) ; 
 scalar_t__ register_framebuffer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_reg (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ivtvfb_init_card(struct ivtv *itv)
{
	int rc;

	if (itv->osd_info) {
		IVTVFB_ERR("Card %d already initialised\n", ivtvfb_card_id);
		return -EBUSY;
	}

	itv->osd_info = kzalloc(sizeof(struct osd_info),
					GFP_ATOMIC|__GFP_NOWARN);
	if (itv->osd_info == NULL) {
		IVTVFB_ERR("Failed to allocate memory for osd_info\n");
		return -ENOMEM;
	}

	/* Find & setup the OSD buffer */
	rc = ivtvfb_init_io(itv);
	if (rc) {
		ivtvfb_release_buffers(itv);
		return rc;
	}

	/* Set the startup video mode information */
	if ((rc = ivtvfb_init_vidmode(itv))) {
		ivtvfb_release_buffers(itv);
		return rc;
	}

	/* Register the framebuffer */
	if (register_framebuffer(&itv->osd_info->ivtvfb_info) < 0) {
		ivtvfb_release_buffers(itv);
		return -EINVAL;
	}

	itv->osd_video_pbase = itv->osd_info->video_pbase;

	/* Set the card to the requested mode */
	ivtvfb_set_par(&itv->osd_info->ivtvfb_info);

	/* Set color 0 to black */
	write_reg(0, 0x02a30);
	write_reg(0, 0x02a34);

	/* Enable the osd */
	ivtvfb_blank(FB_BLANK_UNBLANK, &itv->osd_info->ivtvfb_info);

	/* Enable restart */
	itv->ivtvfb_restore = ivtvfb_restore;

	/* Allocate DMA */
	ivtv_udma_alloc(itv);
	return 0;

}