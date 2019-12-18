#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  address; } ;
typedef  TYPE_1__ vita2d_display_data ;
struct TYPE_6__ {int size; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  pixelformat; int /*<<< orphan*/  pitch; int /*<<< orphan*/  base; } ;
typedef  TYPE_2__ SceDisplayFrameBuf ;

/* Variables and functions */
 int /*<<< orphan*/  DISPLAY_HEIGHT ; 
 int /*<<< orphan*/  DISPLAY_PIXEL_FORMAT ; 
 int /*<<< orphan*/  DISPLAY_STRIDE_IN_PIXELS ; 
 int /*<<< orphan*/  DISPLAY_WIDTH ; 
 int /*<<< orphan*/  SCE_DISPLAY_SETBUF_NEXTFRAME ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  sceDisplaySetFrameBuf (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sceDisplayWaitVblankStart () ; 
 scalar_t__ vblank_wait ; 

__attribute__((used)) static void display_callback(const void *callback_data)
{
	SceDisplayFrameBuf framebuf;
	const vita2d_display_data *display_data = (const vita2d_display_data *)callback_data;

	memset(&framebuf, 0x00, sizeof(SceDisplayFrameBuf));
	framebuf.size        = sizeof(SceDisplayFrameBuf);
	framebuf.base        = display_data->address;
	framebuf.pitch       = DISPLAY_STRIDE_IN_PIXELS;
	framebuf.pixelformat = DISPLAY_PIXEL_FORMAT;
	framebuf.width       = DISPLAY_WIDTH;
	framebuf.height      = DISPLAY_HEIGHT;
	sceDisplaySetFrameBuf(&framebuf, SCE_DISPLAY_SETBUF_NEXTFRAME);

	if (vblank_wait) {
		sceDisplayWaitVblankStart();
	}
}