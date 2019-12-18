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
struct TYPE_4__ {char const* name; char* (* generate_name ) (int /*<<< orphan*/ ,int*) ;int beh; char* help; scalar_t__ var; scalar_t__ data; int /*<<< orphan*/  id; int /*<<< orphan*/  enabled; } ;
typedef  TYPE_1__ menu_entry ;

/* Variables and functions */
#define  MB_NONE 134 
#define  MB_OPT_CUSTOM 133 
#define  MB_OPT_CUSTONOFF 132 
#define  MB_OPT_CUSTRANGE 131 
#define  MB_OPT_ENUM 130 
#define  MB_OPT_ONOFF 129 
#define  MB_OPT_RANGE 128 
 int g_menuscreen_h ; 
 int g_menuscreen_w ; 
 int /*<<< orphan*/  lprintf (char*,...) ; 
 int me_mfont_h ; 
 int me_mfont_w ; 
 int /*<<< orphan*/  me_read_onoff (TYPE_1__ const*) ; 
 int me_sfont_h ; 
 int /*<<< orphan*/  menu_draw_begin (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  menu_draw_end () ; 
 int /*<<< orphan*/  menu_draw_selection (int,int,int) ; 
 scalar_t__* menu_error_msg ; 
 int menu_error_time ; 
 int /*<<< orphan*/  menu_separation () ; 
 int plat_get_ticks_ms () ; 
 int /*<<< orphan*/  smalltext_out16 (int,int,char const*,int) ; 
 char* strchr (char const*,char) ; 
 int strlen (char const*) ; 
 char* stub1 (int /*<<< orphan*/ ,int*) ; 
 char* stub2 (int /*<<< orphan*/ ,int*) ; 
 char* stub3 (int /*<<< orphan*/ ,int*) ; 
 char* stub4 (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  text_out16 (int,int,...) ; 

__attribute__((used)) static void me_draw(const menu_entry *entries, int sel, void (*draw_more)(void))
{
	const menu_entry *ent, *ent_sel = entries;
	int x, y, w = 0, h = 0;
	int offs, col2_offs = 27 * me_mfont_w;
	int vi_sel_ln = 0;
	const char *name;
	int i, n;

	/* calculate size of menu rect */
	for (ent = entries, i = n = 0; ent->name; ent++, i++)
	{
		int wt;

		if (!ent->enabled)
			continue;

		if (i == sel) {
			ent_sel = ent;
			vi_sel_ln = n;
		}

		name = NULL;
		wt = strlen(ent->name) * me_mfont_w;
		if (wt == 0 && ent->generate_name)
			name = ent->generate_name(ent->id, &offs);
		if (name != NULL)
			wt = strlen(name) * me_mfont_w;

		if (ent->beh != MB_NONE)
		{
			if (wt > col2_offs)
				col2_offs = wt + me_mfont_w;
			wt = col2_offs;

			switch (ent->beh) {
			case MB_NONE:
				break;
			case MB_OPT_ONOFF:
			case MB_OPT_RANGE:
				wt += me_mfont_w * 3;
				break;
			case MB_OPT_CUSTOM:
			case MB_OPT_CUSTONOFF:
			case MB_OPT_CUSTRANGE:
				name = NULL;
				offs = 0;
				if (ent->generate_name != NULL)
					name = ent->generate_name(ent->id, &offs);
				if (name != NULL)
					wt += (strlen(name) + offs) * me_mfont_w;
				break;
			case MB_OPT_ENUM:
				wt += 10 * me_mfont_w;
				break;
			}
		}

		if (wt > w)
			w = wt;
		n++;
	}
	h = n * me_mfont_h;
	w += me_mfont_w * 2; /* selector */

	if (w > g_menuscreen_w) {
		lprintf("width %d > %d\n", w, g_menuscreen_w);
		w = g_menuscreen_w;
	}
	if (h > g_menuscreen_h) {
		lprintf("height %d > %d\n", w, g_menuscreen_h);
		h = g_menuscreen_h;
	}

	x = g_menuscreen_w / 2 - w / 2;
	y = g_menuscreen_h / 2 - h / 2;
#ifdef MENU_ALIGN_LEFT
	if (x > 12) x = 12;
#endif

	/* draw */
	menu_draw_begin(1, 0);
	menu_draw_selection(x, y + vi_sel_ln * me_mfont_h, w);
	x += me_mfont_w * 2;

	for (ent = entries; ent->name; ent++)
	{
		const char **names;
		int len, leftname_end = 0;

		if (!ent->enabled)
			continue;

		name = ent->name;
		if (strlen(name) == 0) {
			if (ent->generate_name)
				name = ent->generate_name(ent->id, &offs);
		}
		if (name != NULL) {
			text_out16(x, y, name);
			leftname_end = x + (strlen(name) + 1) * me_mfont_w;
		}

		switch (ent->beh) {
		case MB_NONE:
			break;
		case MB_OPT_ONOFF:
			text_out16(x + col2_offs, y, me_read_onoff(ent) ? "ON" : "OFF");
			break;
		case MB_OPT_RANGE:
			text_out16(x + col2_offs, y, "%i", *(int *)ent->var);
			break;
		case MB_OPT_CUSTOM:
		case MB_OPT_CUSTONOFF:
		case MB_OPT_CUSTRANGE:
			name = NULL;
			offs = 0;
			if (ent->generate_name)
				name = ent->generate_name(ent->id, &offs);
			if (name != NULL)
				text_out16(x + col2_offs + offs * me_mfont_w, y, "%s", name);
			break;
		case MB_OPT_ENUM:
			names = (const char **)ent->data;
			for (i = 0; names[i] != NULL; i++) {
				offs = x + col2_offs;
				len = strlen(names[i]);
				if (len > 10)
					offs += (10 - len - 2) * me_mfont_w;
				if (offs < leftname_end)
					offs = leftname_end;
				if (i == *(unsigned char *)ent->var) {
					text_out16(offs, y, "%s", names[i]);
					break;
				}
			}
			break;
		}

		y += me_mfont_h;
	}

	menu_separation();

	/* display help or message if we have one */
	h = (g_menuscreen_h - h) / 2; // bottom area height
	if (menu_error_msg[0] != 0) {
		if (h >= me_mfont_h + 4)
			text_out16(5, g_menuscreen_h - me_mfont_h - 4, menu_error_msg);
		else
			lprintf("menu msg doesn't fit!\n");

		if (plat_get_ticks_ms() - menu_error_time > 2048)
			menu_error_msg[0] = 0;
	}
	else if (ent_sel->help != NULL) {
		const char *tmp = ent_sel->help;
		int l;
		for (l = 0; tmp != NULL && *tmp != 0; l++)
			tmp = strchr(tmp + 1, '\n');
		if (h >= l * me_sfont_h + 4)
			for (tmp = ent_sel->help; l > 0; l--, tmp = strchr(tmp, '\n') + 1)
				smalltext_out16(5, g_menuscreen_h - (l * me_sfont_h + 4), tmp, 0xffff);
	}

	menu_separation();

	if (draw_more != NULL)
		draw_more();

	menu_draw_end();
}