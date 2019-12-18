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
typedef  int uint16_t ;
struct TYPE_4__ {int h_sync_off; int h_sync_width; int v_sync_off_width; int sync_off_width_high; int dtd_flags; int v_sync_off_high; scalar_t__ reserved; scalar_t__ sdvo_flags; } ;
struct TYPE_3__ {int clock; int h_active; int h_blank; int h_high; int v_active; int v_blank; int v_high; } ;
struct intel_sdvo_dtd {TYPE_2__ part2; TYPE_1__ part1; } ;
struct drm_display_mode {int hdisplay; int vdisplay; int htotal; int hsync_end; int hsync_start; int vtotal; int vsync_end; int vsync_start; int clock; int flags; } ;

/* Variables and functions */
 int DRM_MODE_FLAG_INTERLACE ; 
 int DRM_MODE_FLAG_PHSYNC ; 
 int DRM_MODE_FLAG_PVSYNC ; 
 int DTD_FLAG_HSYNC_POSITIVE ; 
 int DTD_FLAG_INTERLACE ; 
 int DTD_FLAG_VSYNC_POSITIVE ; 
 scalar_t__ intel_mode_get_pixel_multiplier (struct drm_display_mode const*) ; 

__attribute__((used)) static void intel_sdvo_get_dtd_from_mode(struct intel_sdvo_dtd *dtd,
					 const struct drm_display_mode *mode)
{
	uint16_t width, height;
	uint16_t h_blank_len, h_sync_len, v_blank_len, v_sync_len;
	uint16_t h_sync_offset, v_sync_offset;
	int mode_clock;

	width = mode->hdisplay;
	height = mode->vdisplay;

	/* do some mode translations */
	h_blank_len = mode->htotal - mode->hdisplay;
	h_sync_len = mode->hsync_end - mode->hsync_start;

	v_blank_len = mode->vtotal - mode->vdisplay;
	v_sync_len = mode->vsync_end - mode->vsync_start;

	h_sync_offset = mode->hsync_start - mode->hdisplay;
	v_sync_offset = mode->vsync_start - mode->vdisplay;

	mode_clock = mode->clock;
	mode_clock /= intel_mode_get_pixel_multiplier(mode) ?: 1;
	mode_clock /= 10;
	dtd->part1.clock = mode_clock;

	dtd->part1.h_active = width & 0xff;
	dtd->part1.h_blank = h_blank_len & 0xff;
	dtd->part1.h_high = (((width >> 8) & 0xf) << 4) |
		((h_blank_len >> 8) & 0xf);
	dtd->part1.v_active = height & 0xff;
	dtd->part1.v_blank = v_blank_len & 0xff;
	dtd->part1.v_high = (((height >> 8) & 0xf) << 4) |
		((v_blank_len >> 8) & 0xf);

	dtd->part2.h_sync_off = h_sync_offset & 0xff;
	dtd->part2.h_sync_width = h_sync_len & 0xff;
	dtd->part2.v_sync_off_width = (v_sync_offset & 0xf) << 4 |
		(v_sync_len & 0xf);
	dtd->part2.sync_off_width_high = ((h_sync_offset & 0x300) >> 2) |
		((h_sync_len & 0x300) >> 4) | ((v_sync_offset & 0x30) >> 2) |
		((v_sync_len & 0x30) >> 4);

	dtd->part2.dtd_flags = 0x18;
	if (mode->flags & DRM_MODE_FLAG_INTERLACE)
		dtd->part2.dtd_flags |= DTD_FLAG_INTERLACE;
	if (mode->flags & DRM_MODE_FLAG_PHSYNC)
		dtd->part2.dtd_flags |= DTD_FLAG_HSYNC_POSITIVE;
	if (mode->flags & DRM_MODE_FLAG_PVSYNC)
		dtd->part2.dtd_flags |= DTD_FLAG_VSYNC_POSITIVE;

	dtd->part2.sdvo_flags = 0;
	dtd->part2.v_sync_off_high = v_sync_offset & 0xc0;
	dtd->part2.reserved = 0;
}