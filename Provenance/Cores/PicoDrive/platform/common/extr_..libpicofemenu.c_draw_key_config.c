#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  mask; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ me_bind_action ;
typedef  int /*<<< orphan*/  buff2 ;
typedef  int /*<<< orphan*/  buff ;

/* Variables and functions */
 int /*<<< orphan*/  PBTN_MA2 ; 
 int /*<<< orphan*/  PBTN_MOK ; 
 int /*<<< orphan*/  action_binds (int,int /*<<< orphan*/ ,int) ; 
 int g_menuscreen_h ; 
 int g_menuscreen_w ; 
 char* in_get_dev_name (int,int /*<<< orphan*/ ,int) ; 
 char* in_get_key_name (int,int /*<<< orphan*/ ) ; 
 int me_mfont_h ; 
 int me_mfont_w ; 
 int /*<<< orphan*/  menu_draw_begin (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  menu_draw_end () ; 
 int /*<<< orphan*/  menu_draw_selection (int,int,int) ; 
 int /*<<< orphan*/  menu_separation () ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,...) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  text_out16 (int,int,char const*,...) ; 

__attribute__((used)) static void draw_key_config(const me_bind_action *opts, int opt_cnt, int player_idx,
		int sel, int dev_id, int dev_count, int is_bind)
{
	char buff[64], buff2[32];
	const char *dev_name;
	int x, y, w, i;

	w = ((player_idx >= 0) ? 20 : 30) * me_mfont_w;
	x = g_menuscreen_w / 2 - w / 2;
	y = (g_menuscreen_h - 4 * me_mfont_h) / 2 - (2 + opt_cnt) * me_mfont_h / 2;
	if (x < me_mfont_w * 2)
		x = me_mfont_w * 2;

	menu_draw_begin(1, 0);
	if (player_idx >= 0)
		text_out16(x, y, "Player %i controls", player_idx + 1);
	else
		text_out16(x, y, "Emulator controls");

	y += 2 * me_mfont_h;
	menu_draw_selection(x - me_mfont_w * 2, y + sel * me_mfont_h, w + 2 * me_mfont_w);

	for (i = 0; i < opt_cnt; i++, y += me_mfont_h)
		text_out16(x, y, "%s : %s", opts[i].name,
			action_binds(player_idx, opts[i].mask, dev_id));

	menu_separation();

	if (dev_id < 0)
		dev_name = "(all devices)";
	else
		dev_name = in_get_dev_name(dev_id, 0, 1);
	w = strlen(dev_name) * me_mfont_w;
	if (w < 30 * me_mfont_w)
		w = 30 * me_mfont_w;
	if (w > g_menuscreen_w)
		w = g_menuscreen_w;

	x = g_menuscreen_w / 2 - w / 2;

	if (!is_bind) {
		snprintf(buff2, sizeof(buff2), "%s", in_get_key_name(-1, -PBTN_MOK));
		snprintf(buff, sizeof(buff), "%s - bind, %s - clear", buff2,
				in_get_key_name(-1, -PBTN_MA2));
		text_out16(x, g_menuscreen_h - 4 * me_mfont_h, buff);
	}
	else
		text_out16(x, g_menuscreen_h - 4 * me_mfont_h, "Press a button to bind/unbind");

	if (dev_count > 1) {
		text_out16(x, g_menuscreen_h - 3 * me_mfont_h, dev_name);
		text_out16(x, g_menuscreen_h - 2 * me_mfont_h, "Press left/right for other devs");
	}

	menu_draw_end();
}