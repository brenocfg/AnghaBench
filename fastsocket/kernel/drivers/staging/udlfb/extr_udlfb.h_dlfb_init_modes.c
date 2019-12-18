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
struct TYPE_2__ {int xres; int yres; int /*<<< orphan*/  unknown3; int /*<<< orphan*/  unknown2; int /*<<< orphan*/  unknown1; int /*<<< orphan*/  vclock; int /*<<< orphan*/  hclock; scalar_t__ col; } ;

/* Variables and functions */
 TYPE_1__* dlfb_video_modes ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static void dlfb_init_modes(void)
{
	dlfb_video_modes[0].col = 0;
	memcpy(&dlfb_video_modes[0].hclock, "\x20\x3C\x7A\xC9", 4);
	memcpy(&dlfb_video_modes[0].vclock, "\xF2\x6C\x48\xF9", 4);
	memcpy(&dlfb_video_modes[0].unknown1, "\x70\x53\xFF\xFF\x21\x27", 6);
	dlfb_video_modes[0].xres = 800;
	memcpy(&dlfb_video_modes[0].unknown2, "\x91\xF3\xFF\xFF\xFF\xF9", 6);
	dlfb_video_modes[0].yres = 480;
	memcpy(&dlfb_video_modes[0].unknown3, "\x01\x02\xC8\x19", 4);

	dlfb_video_modes[1].col = 0;
	memcpy(&dlfb_video_modes[1].hclock, "\x36\x18\xD5\x10", 4);
	memcpy(&dlfb_video_modes[1].vclock, "\x60\xA9\x7B\x33", 4);
	memcpy(&dlfb_video_modes[1].unknown1, "\xA1\x2B\x27\x32\xFF\xFF", 6);
	dlfb_video_modes[1].xres = 1024;
	memcpy(&dlfb_video_modes[1].unknown2, "\xD9\x9A\xFF\xCA\xFF\xFF", 6);
	dlfb_video_modes[1].yres = 768;
	memcpy(&dlfb_video_modes[1].unknown3, "\x04\x03\xC8\x32", 4);

	dlfb_video_modes[2].col = 0;
	memcpy(&dlfb_video_modes[2].hclock, "\x98\xF8\x0D\x57", 4);
	memcpy(&dlfb_video_modes[2].vclock, "\x2A\x55\x4D\x54", 4);
	memcpy(&dlfb_video_modes[2].unknown1, "\xCA\x0D\xFF\xFF\x94\x43", 6);
	dlfb_video_modes[2].xres = 1280;
	memcpy(&dlfb_video_modes[2].unknown2, "\x9A\xA8\xFF\xFF\xFF\xF9", 6);
	dlfb_video_modes[2].yres = 1024;
	memcpy(&dlfb_video_modes[2].unknown3, "\x04\x02\x60\x54", 4);

	dlfb_video_modes[3].col = 0;
	memcpy(&dlfb_video_modes[3].hclock, "\x42\x24\x38\x36", 4);
	memcpy(&dlfb_video_modes[3].vclock, "\xC1\x52\xD9\x29", 4);
	memcpy(&dlfb_video_modes[3].unknown1, "\xEA\xB8\x32\x60\xFF\xFF", 6);
	dlfb_video_modes[3].xres = 1400;
	memcpy(&dlfb_video_modes[3].unknown2, "\xC9\x4E\xFF\xFF\xFF\xF2", 6);
	dlfb_video_modes[3].yres = 1050;
	memcpy(&dlfb_video_modes[3].unknown3, "\x04\x02\x1E\x5F", 4);
}