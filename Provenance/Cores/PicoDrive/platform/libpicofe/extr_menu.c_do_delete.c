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
typedef  int /*<<< orphan*/  tmp ;

/* Variables and functions */
 int PBTN_MA2 ; 
 int PBTN_MA3 ; 
 int PBTN_MBACK ; 
 int PBTN_MENU ; 
 int g_menuscreen_w ; 
 char* in_get_key_name (int,int) ; 
 int in_menu_wait (int,int /*<<< orphan*/ *,int) ; 
 int in_menu_wait_any (int /*<<< orphan*/ *,int) ; 
 int me_mfont_h ; 
 int me_mfont_w ; 
 int me_sfont_w ; 
 int /*<<< orphan*/  menu_draw_begin (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  menu_draw_end () ; 
 int /*<<< orphan*/  remove (char const*) ; 
 int /*<<< orphan*/  smalltext_out16 (int,int,char const*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  text_out16 (int,int,char*) ; 

__attribute__((used)) static void do_delete(const char *fpath, const char *fname)
{
	int len, mid, inp;
	const char *nm;
	char tmp[64];

	menu_draw_begin(1, 0);

	len = strlen(fname);
	if (len > g_menuscreen_w / me_sfont_w)
		len = g_menuscreen_w / me_sfont_w;

	mid = g_menuscreen_w / 2;
	text_out16(mid - me_mfont_w * 15 / 2,  8 * me_mfont_h, "About to delete");
	smalltext_out16(mid - len * me_sfont_w / 2, 9 * me_mfont_h + 5, fname, 0xbdff);
	text_out16(mid - me_mfont_w * 13 / 2, 11 * me_mfont_h, "Are you sure?");

	nm = in_get_key_name(-1, -PBTN_MA3);
	snprintf(tmp, sizeof(tmp), "(%s - confirm, ", nm);
	len = strlen(tmp);
	nm = in_get_key_name(-1, -PBTN_MBACK);
	snprintf(tmp + len, sizeof(tmp) - len, "%s - cancel)", nm);
	len = strlen(tmp);

	text_out16(mid - me_mfont_w * len / 2, 12 * me_mfont_h, tmp);
	menu_draw_end();

	while (in_menu_wait_any(NULL, 50) & (PBTN_MENU|PBTN_MA2));
	inp = in_menu_wait(PBTN_MA3|PBTN_MBACK, NULL, 100);
	if (inp & PBTN_MA3)
		remove(fpath);
}