#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int menu_id ;
struct TYPE_4__ {int* reg; } ;
struct TYPE_6__ {TYPE_1__ video; } ;
struct TYPE_5__ {float scale; float hscale40; float hscale32; int EmuOpt; } ;

/* Variables and functions */
#define  MA_OPT3_BLACKLVL 138 
#define  MA_OPT3_DONE 137 
#define  MA_OPT3_FILTERING 136 
#define  MA_OPT3_GAMMAA 135 
#define  MA_OPT3_HSCALE32 134 
#define  MA_OPT3_HSCALE40 133 
#define  MA_OPT3_PRES_FULLSCR 132 
#define  MA_OPT3_PRES_NOSCALE 131 
#define  MA_OPT3_PRES_SCALE43 130 
#define  MA_OPT3_SCALE 129 
#define  MA_OPT3_VSYNC 128 
 int /*<<< orphan*/  OPT3_ENTRY_COUNT ; 
 unsigned long PBTN_CIRCLE ; 
 unsigned long PBTN_DOWN ; 
 unsigned long PBTN_LEFT ; 
 unsigned long PBTN_RIGHT ; 
 unsigned long PBTN_UP ; 
 unsigned long PBTN_X ; 
 TYPE_3__ Pico ; 
 TYPE_2__ currentConfig ; 
 int /*<<< orphan*/  draw_dispmenu_options (int) ; 
 unsigned long in_menu_wait (unsigned long,int /*<<< orphan*/ ) ; 
 int me_count_enabled (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int me_index2id (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  me_process (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  menu_opt3_preview (int) ; 
 int /*<<< orphan*/  opt3_entries ; 
 unsigned long psp_pad_read (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dispmenu_loop_options(void)
{
	static int menu_sel = 0;
	int menu_sel_max, is_32col = (Pico.video.reg[12]&1)^1;
	unsigned long inp = 0;
	menu_id selected_id;

	menu_sel_max = me_count_enabled(opt3_entries, OPT3_ENTRY_COUNT) - 1;

	for (;;)
	{
		draw_dispmenu_options(menu_sel);
		inp = in_menu_wait(PBTN_UP|PBTN_DOWN|PBTN_LEFT|PBTN_RIGHT|PBTN_X|PBTN_CIRCLE, 0);
		if (inp & PBTN_UP  ) { menu_sel--; if (menu_sel < 0) menu_sel = menu_sel_max; }
		if (inp & PBTN_DOWN) { menu_sel++; if (menu_sel > menu_sel_max) menu_sel = 0; }
		selected_id = me_index2id(opt3_entries, OPT3_ENTRY_COUNT, menu_sel);
		if (selected_id == MA_OPT3_HSCALE40 &&  is_32col) { is_32col = 0; menu_opt3_preview(is_32col); }
		if (selected_id == MA_OPT3_HSCALE32 && !is_32col) { is_32col = 1; menu_opt3_preview(is_32col); }

		if (inp & (PBTN_LEFT|PBTN_RIGHT)) // multi choise
		{
			float *setting = NULL;
			int tmp;
			me_process(opt3_entries, OPT3_ENTRY_COUNT, selected_id, (inp&PBTN_RIGHT) ? 1 : 0);
			switch (selected_id) {
				case MA_OPT3_SCALE:	setting = &currentConfig.scale; break;
				case MA_OPT3_HSCALE40:	setting = &currentConfig.hscale40; is_32col = 0; break;
				case MA_OPT3_HSCALE32:	setting = &currentConfig.hscale32; is_32col = 1; break;
				case MA_OPT3_FILTERING:
				case MA_OPT3_GAMMAA:
				case MA_OPT3_BLACKLVL:	menu_opt3_preview(is_32col); break;
				case MA_OPT3_VSYNC:
					tmp = ((currentConfig.EmuOpt>>13)&1) | ((currentConfig.EmuOpt>>15)&2);
					tmp = (inp & PBTN_LEFT) ? (tmp>>1) : ((tmp<<1)|1);
					if (tmp > 3) tmp = 3;
					currentConfig.EmuOpt &= ~0x12000;
					currentConfig.EmuOpt |= ((tmp&2)<<15) | ((tmp&1)<<13);
					break;
				default: break;
			}
			if (setting != NULL) {
				while ((inp = psp_pad_read(0)) & (PBTN_LEFT|PBTN_RIGHT)) {
					*setting += (inp & PBTN_LEFT) ? -0.01 : 0.01;
					if (*setting <= 0) *setting = 0.01;
					menu_opt3_preview(is_32col);
					draw_dispmenu_options(menu_sel); // will wait vsync
				}
			}
		}
		if (inp & PBTN_CIRCLE) { // toggleable options
			me_process(opt3_entries, OPT3_ENTRY_COUNT, selected_id, 1);
			switch (selected_id) {
				case MA_OPT3_DONE:
					return;
				case MA_OPT3_PRES_NOSCALE:
					currentConfig.scale = currentConfig.hscale40 = currentConfig.hscale32 = 1.0;
					menu_opt3_preview(is_32col);
					break;
				case MA_OPT3_PRES_SCALE43:
					currentConfig.scale = 1.20;
					currentConfig.hscale40 = 1.00;
					currentConfig.hscale32 = 1.25;
					menu_opt3_preview(is_32col);
					break;
				case MA_OPT3_PRES_FULLSCR:
					currentConfig.scale = 1.20;
					currentConfig.hscale40 = 1.25;
					currentConfig.hscale32 = 1.56;
					menu_opt3_preview(is_32col);
					break;
				case MA_OPT3_FILTERING:
					menu_opt3_preview(is_32col);
					break;
				default: break;
			}
		}
		if (inp & PBTN_X) return;
	}
}