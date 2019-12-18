#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;
struct dum_ch_setup {int xmin; int ymin; int xmax; int ymax; int minadr; int maxadr; int dirtybuffer; scalar_t__ slave_trans; scalar_t__ hwdirty; int /*<<< orphan*/  format; int /*<<< orphan*/  pad; scalar_t__ rotate; scalar_t__ ymirror; scalar_t__ xmirror; scalar_t__ disp_no; } ;

/* Variables and functions */
 int DISP_MAX_X_SIZE ; 
 int DISP_MAX_Y_SIZE ; 
 int /*<<< orphan*/  PAD_1024 ; 
 int /*<<< orphan*/  RGB888 ; 
 int dum_ch_setup (int,struct dum_ch_setup*) ; 

__attribute__((used)) static u32 display_open(int ch_no, int auto_update, u32 * dirty_buffer,
			u32 * frame_buffer, u32 xpos, u32 ypos, u32 w, u32 h)
{

	struct dum_ch_setup k;
	int ret;

	/* keep width & height within display area */
	if ((xpos + w) > DISP_MAX_X_SIZE)
		w = DISP_MAX_X_SIZE - xpos;

	if ((ypos + h) > DISP_MAX_Y_SIZE)
		h = DISP_MAX_Y_SIZE - ypos;

	/* assume 1 display only */
	k.disp_no = 0;
	k.xmin = xpos;
	k.ymin = ypos;
	k.xmax = xpos + (w - 1);
	k.ymax = ypos + (h - 1);

	/* adjust min and max values if necessary */
	if (k.xmin > DISP_MAX_X_SIZE - 1)
		k.xmin = DISP_MAX_X_SIZE - 1;
	if (k.ymin > DISP_MAX_Y_SIZE - 1)
		k.ymin = DISP_MAX_Y_SIZE - 1;

	if (k.xmax > DISP_MAX_X_SIZE - 1)
		k.xmax = DISP_MAX_X_SIZE - 1;
	if (k.ymax > DISP_MAX_Y_SIZE - 1)
		k.ymax = DISP_MAX_Y_SIZE - 1;

	k.xmirror = 0;
	k.ymirror = 0;
	k.rotate = 0;
	k.minadr = (u32) frame_buffer;
	k.maxadr = (u32) frame_buffer + (((w - 1) << 10) | ((h << 2) - 2));
	k.pad = PAD_1024;
	k.dirtybuffer = (u32) dirty_buffer;
	k.format = RGB888;
	k.hwdirty = 0;
	k.slave_trans = 0;

	ret = dum_ch_setup(ch_no, &k);

	return ret;
}