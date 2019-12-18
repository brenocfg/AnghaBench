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
struct TYPE_4__ {int con_xres; int con_yres; int con_cols; int con_rows; int con_stride; int tgt_stride; int target_x; int target_y; int /*<<< orphan*/  background; int /*<<< orphan*/  foreground; int /*<<< orphan*/  font; void* destbuffer; } ;
typedef  TYPE_1__ console_data_s ;

/* Variables and functions */
 int /*<<< orphan*/  COLOR_BLACK ; 
 int /*<<< orphan*/  COLOR_WHITE ; 
 int FONT_XSIZE ; 
 int FONT_YSIZE ; 
 size_t STD_ERR ; 
 size_t STD_OUT ; 
 int /*<<< orphan*/  _CPU_ISR_Disable (unsigned int) ; 
 int /*<<< orphan*/  _CPU_ISR_Restore (unsigned int) ; 
 int /*<<< orphan*/  _IONBF ; 
 int /*<<< orphan*/  __console_clear () ; 
 int /*<<< orphan*/  console_font_8x16 ; 
 TYPE_1__* curr_con ; 
 int /*<<< orphan*/ ** devoptab_list ; 
 int /*<<< orphan*/  dotab_stdout ; 
 int /*<<< orphan*/  setvbuf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ stdcon ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 

void __console_init(void *framebuffer,int xstart,int ystart,int xres,int yres,int stride)
{
	unsigned int level;
	console_data_s *con = &stdcon;

	_CPU_ISR_Disable(level);

	con->destbuffer = framebuffer;
	con->con_xres = xres;
	con->con_yres = yres;
	con->con_cols = xres / FONT_XSIZE;
	con->con_rows = yres / FONT_YSIZE;
	con->con_stride = con->tgt_stride = stride;
	con->target_x = xstart;
	con->target_y = ystart;

	con->font = console_font_8x16;

	con->foreground = COLOR_WHITE;
	con->background = COLOR_BLACK;

	curr_con = con;

	__console_clear();

	devoptab_list[STD_OUT] = &dotab_stdout;
	devoptab_list[STD_ERR] = &dotab_stdout;
	_CPU_ISR_Restore(level);

	setvbuf(stdout, NULL , _IONBF, 0);
	setvbuf(stderr, NULL , _IONBF, 0);
}