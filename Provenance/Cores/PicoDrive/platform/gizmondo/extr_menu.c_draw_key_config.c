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

/* Variables and functions */
 int /*<<< orphan*/  action_binds (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  menu_draw_begin (int) ; 
 int /*<<< orphan*/  menu_draw_end () ; 
 int /*<<< orphan*/  menu_draw_selection (int,int,int) ; 
 int /*<<< orphan*/  text_out16 (int,int,char*,...) ; 

__attribute__((used)) static void draw_key_config(const me_bind_action *opts, int opt_cnt, int player_idx, int sel)
{
	int x, y, tl_y = 30, i;

	menu_draw_begin(1);
	if (player_idx >= 0) {
		text_out16(80, 10, "Player %i controls", player_idx + 1);
		x = 80;
	} else {
		text_out16(80, 10, "Emulator controls");
		x = 40;
	}

	menu_draw_selection(x - 16, tl_y + sel*10, (player_idx >= 0) ? 66 : 130);

	y = tl_y;
	for (i = 0; i < opt_cnt; i++, y+=10)
		text_out16(x, y, "%s : %s", opts[i].name, action_binds(player_idx, opts[i].mask));

	text_out16(x, y, "Done");

	if (sel < opt_cnt) {
		text_out16(30, 195, "Press a button to bind/unbind");
		text_out16(30, 205, "Use HOME to clear");
		text_out16(30, 215, "To bind UP/DOWN, hold HOME");
		text_out16(30, 225, "Select \"Done\" to exit");
	} else {
		text_out16(30, 205, "Use Options -> Save cfg");
		text_out16(30, 215, "to save controls");
		text_out16(30, 225, "Press PLAY or STOP to exit");
	}
	menu_draw_end();
}