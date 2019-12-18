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
typedef  int u8 ;
struct TYPE_4__ {scalar_t__ version; TYPE_1__* extif; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* write_data ) (int*,int) ;int /*<<< orphan*/  (* write_command ) (int*,int) ;int /*<<< orphan*/  (* set_bits_per_cycle ) (int) ;} ;

/* Variables and functions */
 int BLIZZARD_INPUT_WIN_X_START_0 ; 
 int BLIZZARD_SRC_WRITE_LCD ; 
 int BLIZZARD_SRC_WRITE_LCD_BACKGROUND ; 
 int BLIZZARD_SRC_WRITE_LCD_DESTRUCTIVE ; 
 int BLIZZARD_SRC_WRITE_OVERLAY_ENABLE ; 
 scalar_t__ BLIZZARD_VERSION_S1D13744 ; 
 scalar_t__ BLIZZARD_VERSION_S1D13745 ; 
 int OMAPFB_FORMAT_FLAG_ENABLE_OVERLAY ; 
 TYPE_2__ blizzard ; 
 int /*<<< orphan*/  stub1 (int) ; 
 int /*<<< orphan*/  stub2 (int*,int) ; 
 int /*<<< orphan*/  stub3 (int*,int) ; 

__attribute__((used)) static void set_window_regs(int x_start, int y_start, int x_end, int y_end,
			    int x_out_start, int y_out_start,
			    int x_out_end, int y_out_end, int color_mode,
			    int zoom_off, int flags)
{
	u8 tmp[18];
	u8 cmd;

	x_end--;
	y_end--;
	tmp[0] = x_start;
	tmp[1] = x_start >> 8;
	tmp[2] = y_start;
	tmp[3] = y_start >> 8;
	tmp[4] = x_end;
	tmp[5] = x_end >> 8;
	tmp[6] = y_end;
	tmp[7] = y_end >> 8;

	x_out_end--;
	y_out_end--;
	tmp[8]  = x_out_start;
	tmp[9]  = x_out_start >> 8;
	tmp[10] = y_out_start;
	tmp[11] = y_out_start >> 8;
	tmp[12] = x_out_end;
	tmp[13] = x_out_end >> 8;
	tmp[14] = y_out_end;
	tmp[15] = y_out_end >> 8;

	tmp[16] = color_mode;
	if (zoom_off && blizzard.version == BLIZZARD_VERSION_S1D13745)
		tmp[17] = BLIZZARD_SRC_WRITE_LCD_BACKGROUND;
	else if (flags & OMAPFB_FORMAT_FLAG_ENABLE_OVERLAY)
		tmp[17] = BLIZZARD_SRC_WRITE_OVERLAY_ENABLE;
	else
		tmp[17] = blizzard.version == BLIZZARD_VERSION_S1D13744 ?
				BLIZZARD_SRC_WRITE_LCD :
				BLIZZARD_SRC_WRITE_LCD_DESTRUCTIVE;

	blizzard.extif->set_bits_per_cycle(8);
	cmd = BLIZZARD_INPUT_WIN_X_START_0;
	blizzard.extif->write_command(&cmd, 1);
	blizzard.extif->write_data(tmp, 18);
}