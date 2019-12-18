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
struct dirent {scalar_t__ d_type; char* d_name; } ;
typedef  int /*<<< orphan*/  buff ;

/* Variables and functions */
 scalar_t__ DT_DIR ; 
 int /*<<< orphan*/  PBTN_MA2 ; 
 int /*<<< orphan*/  PBTN_MA3 ; 
 int /*<<< orphan*/  PBTN_MBACK ; 
 int /*<<< orphan*/  PBTN_MOK ; 
 unsigned short fname2color (char*) ; 
 scalar_t__ g_autostateld_opt ; 
 scalar_t__ g_menu_filter_off ; 
 int g_menuscreen_h ; 
 scalar_t__ g_menuscreen_ptr ; 
 int g_menuscreen_w ; 
 char* in_get_key_name (int,int /*<<< orphan*/ ) ; 
 int me_mfont_w ; 
 int me_sfont_h ; 
 int me_sfont_w ; 
 int /*<<< orphan*/  menu_darken_bg (void*,void*,int,int) ; 
 int /*<<< orphan*/  menu_draw_begin (int,int) ; 
 int /*<<< orphan*/  menu_draw_end () ; 
 int /*<<< orphan*/  smalltext_out16 (int,int,char*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,...) ; 

__attribute__((used)) static void draw_dirlist(char *curdir, struct dirent **namelist,
	int n, int sel, int show_help)
{
	int max_cnt, start, i, x, pos;
	void *darken_ptr;
	char buff[64];

	max_cnt = g_menuscreen_h / me_sfont_h;
	start = max_cnt / 2 - sel;
	n--; // exclude current dir (".")

	menu_draw_begin(1, 1);

//	if (!rom_loaded)
//		menu_darken_bg(gp2x_screen, 320*240, 0);

	darken_ptr = (short *)g_menuscreen_ptr + g_menuscreen_w * max_cnt/2 * me_sfont_h;
	menu_darken_bg(darken_ptr, darken_ptr, g_menuscreen_w * me_sfont_h * 8 / 10, 0);

	x = 5 + me_mfont_w + 1;
	if (start - 2 >= 0)
		smalltext_out16(14, (start - 2) * me_sfont_h, curdir, 0xffff);
	for (i = 0; i < n; i++) {
		pos = start + i;
		if (pos < 0)  continue;
		if (pos >= max_cnt) break;
		if (namelist[i+1]->d_type == DT_DIR) {
			smalltext_out16(x, pos * me_sfont_h, "/", 0xfff6);
			smalltext_out16(x + me_sfont_w, pos * me_sfont_h, namelist[i+1]->d_name, 0xfff6);
		} else {
			unsigned short color = fname2color(namelist[i+1]->d_name);
			smalltext_out16(x, pos * me_sfont_h, namelist[i+1]->d_name, color);
		}
	}
	smalltext_out16(5, max_cnt/2 * me_sfont_h, ">", 0xffff);

	if (show_help) {
		darken_ptr = (short *)g_menuscreen_ptr
			+ g_menuscreen_w * (g_menuscreen_h - me_sfont_h * 5 / 2);
		menu_darken_bg(darken_ptr, darken_ptr,
			g_menuscreen_w * (me_sfont_h * 5 / 2), 1);

		snprintf(buff, sizeof(buff), "%s - select, %s - back",
			in_get_key_name(-1, -PBTN_MOK), in_get_key_name(-1, -PBTN_MBACK));
		smalltext_out16(x, g_menuscreen_h - me_sfont_h * 3 - 2, buff, 0xe78c);

		snprintf(buff, sizeof(buff), g_menu_filter_off ?
			 "%s - hide unknown files" : "%s - show all files",
			in_get_key_name(-1, -PBTN_MA3));
		smalltext_out16(x, g_menuscreen_h - me_sfont_h * 2 - 2, buff, 0xe78c);

		snprintf(buff, sizeof(buff), g_autostateld_opt ?
			 "%s - autoload save is ON" : "%s - autoload save is OFF",
			in_get_key_name(-1, -PBTN_MA2));
		smalltext_out16(x, g_menuscreen_h - me_sfont_h * 1 - 2, buff, 0xe78c);
	}

	menu_draw_end();
}