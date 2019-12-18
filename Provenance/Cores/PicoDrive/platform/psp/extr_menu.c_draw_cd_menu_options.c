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
struct bios_names_t {int /*<<< orphan*/  jp; int /*<<< orphan*/  eu; int /*<<< orphan*/  us; } ;
typedef  scalar_t__ menu_id ;

/* Variables and functions */
 int /*<<< orphan*/  CDOPT_ENTRY_COUNT ; 
 scalar_t__ MA_CDOPT_TESTBIOS_EUR ; 
 scalar_t__ MA_CDOPT_TESTBIOS_JAP ; 
 scalar_t__ MA_CDOPT_TESTBIOS_USA ; 
 int PicoCDBuffers ; 
 int /*<<< orphan*/  cdopt_entries ; 
 int /*<<< orphan*/  me_draw (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,struct bios_names_t*) ; 
 scalar_t__ me_index2id (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  menu_cdopt_cust_draw ; 
 int /*<<< orphan*/  menu_draw_begin () ; 
 int /*<<< orphan*/  menu_draw_end () ; 
 int /*<<< orphan*/  menu_draw_selection (int,int,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  text_out16 (int,int,char*) ; 

__attribute__((used)) static void draw_cd_menu_options(int menu_sel, struct bios_names_t *bios_names)
{
	int tl_x = 80+25, tl_y = 16+60;
	menu_id selected_id;
	char ra_buff[16];

	if (PicoCDBuffers > 1) sprintf(ra_buff, "%5iK", PicoCDBuffers * 2);
	else strcpy(ra_buff, "     OFF");

	menu_draw_begin();

	menu_draw_selection(tl_x - 16, tl_y + menu_sel*10, 246);

	me_draw(cdopt_entries, CDOPT_ENTRY_COUNT, tl_x, tl_y, menu_cdopt_cust_draw, bios_names);

	selected_id = me_index2id(cdopt_entries, CDOPT_ENTRY_COUNT, menu_sel);
	if ((selected_id == MA_CDOPT_TESTBIOS_USA && strcmp(bios_names->us, "NOT FOUND")) ||
		(selected_id == MA_CDOPT_TESTBIOS_EUR && strcmp(bios_names->eu, "NOT FOUND")) ||
		(selected_id == MA_CDOPT_TESTBIOS_JAP && strcmp(bios_names->jp, "NOT FOUND")))
			text_out16(tl_x, 250, "Press start to test selected BIOS");

	menu_draw_end();
}