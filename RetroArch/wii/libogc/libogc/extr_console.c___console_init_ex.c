#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int target_x; int target_y; int con_xres; int con_yres; int tgt_stride; int con_stride; int con_cols; int con_rows; int /*<<< orphan*/  background; int /*<<< orphan*/  foreground; int /*<<< orphan*/  font; scalar_t__ saved_col; scalar_t__ saved_row; scalar_t__ cursor_col; scalar_t__ cursor_row; void* destbuffer; } ;
typedef  TYPE_1__ console_data_s ;

/* Variables and functions */
 int /*<<< orphan*/  COLOR_BLACK ; 
 int /*<<< orphan*/  COLOR_WHITE ; 
 int FONT_XSIZE ; 
 int FONT_YSIZE ; 
 size_t STD_ERR ; 
 size_t STD_OUT ; 
 int /*<<< orphan*/  VIDEO_SetPostRetraceCallback (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _CPU_ISR_Disable (unsigned int) ; 
 int /*<<< orphan*/  _CPU_ISR_Restore (unsigned int) ; 
 int /*<<< orphan*/  _IONBF ; 
 int /*<<< orphan*/  __console_clear () ; 
 int /*<<< orphan*/  __console_vipostcb ; 
 int /*<<< orphan*/  console_font_8x16 ; 
 TYPE_1__* curr_con ; 
 int /*<<< orphan*/ ** devoptab_list ; 
 int /*<<< orphan*/  dotab_stdout ; 
 int /*<<< orphan*/  setvbuf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ stdcon ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 

void __console_init_ex(void *conbuffer,int tgt_xstart,int tgt_ystart,int tgt_stride,int con_xres,int con_yres,int con_stride)
{
	unsigned int level;
	console_data_s *con = &stdcon;

	_CPU_ISR_Disable(level);

	con->destbuffer = conbuffer;
	con->target_x = tgt_xstart;
	con->target_y = tgt_ystart;
	con->con_xres = con_xres;
	con->con_yres = con_yres;
	con->tgt_stride = tgt_stride;
	con->con_stride = con_stride;
	con->con_cols = con_xres / FONT_XSIZE;
	con->con_rows = con_yres / FONT_YSIZE;
	con->cursor_row = 0;
	con->cursor_col = 0;
	con->saved_row = 0;
	con->saved_col = 0;

	con->font = console_font_8x16;

	con->foreground = COLOR_WHITE;
	con->background = COLOR_BLACK;

	curr_con = con;

	__console_clear();

	devoptab_list[STD_OUT] = &dotab_stdout;
	devoptab_list[STD_ERR] = &dotab_stdout;

	VIDEO_SetPostRetraceCallback(__console_vipostcb);

	_CPU_ISR_Restore(level);

	setvbuf(stdout, NULL , _IONBF, 0);
	setvbuf(stderr, NULL , _IONBF, 0);
}