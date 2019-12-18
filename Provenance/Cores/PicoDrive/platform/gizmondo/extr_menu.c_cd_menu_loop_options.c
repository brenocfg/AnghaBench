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
struct bios_names_t {scalar_t__* jp; scalar_t__* eu; scalar_t__* us; } ;
typedef  int menu_id ;

/* Variables and functions */
 int /*<<< orphan*/  CDOPT_ENTRY_COUNT ; 
 int MA_CDOPT_DONE ; 
 int MA_CDOPT_READAHEAD ; 
#define  MA_CDOPT_TESTBIOS_EUR 130 
#define  MA_CDOPT_TESTBIOS_JAP 129 
#define  MA_CDOPT_TESTBIOS_USA 128 
 unsigned long PBTN_DOWN ; 
 unsigned long PBTN_LEFT ; 
 unsigned long PBTN_PLAY ; 
 unsigned long PBTN_REW ; 
 unsigned long PBTN_RIGHT ; 
 unsigned long PBTN_STOP ; 
 unsigned long PBTN_UP ; 
 int /*<<< orphan*/  PGS_ReloadRom ; 
 int PicoCDBuffers ; 
 int /*<<< orphan*/  cdopt_entries ; 
 int /*<<< orphan*/  draw_cd_menu_options (int,struct bios_names_t*) ; 
 scalar_t__ emu_findBios (int,char**) ; 
 int /*<<< orphan*/  engineState ; 
 unsigned long in_menu_wait (unsigned long) ; 
 int me_index2id (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  me_process (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__* romFileName ; 
 int /*<<< orphan*/  strcpy (scalar_t__*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncpy (scalar_t__*,char*,int) ; 

__attribute__((used)) static void cd_menu_loop_options(void)
{
	static int menu_sel = 0;
	int menu_sel_max = 10;
	unsigned long inp = 0;
	struct bios_names_t bios_names;
	menu_id selected_id;
	char *bios, *p;

	if (emu_findBios(4, &bios)) { // US
		for (p = bios+strlen(bios)-1; p > bios && *p != '/'; p--);
		if (*p == '/') p++;
		strncpy(bios_names.us, p, sizeof(bios_names.us)); bios_names.us[sizeof(bios_names.us)-1] = 0;
	} else	strcpy(bios_names.us, "NOT FOUND");

	if (emu_findBios(8, &bios)) { // EU
		for (p = bios+strlen(bios)-1; p > bios && *p != '/'; p--);
		if (*p == '/') p++;
		strncpy(bios_names.eu, p, sizeof(bios_names.eu)); bios_names.eu[sizeof(bios_names.eu)-1] = 0;
	} else	strcpy(bios_names.eu, "NOT FOUND");

	if (emu_findBios(1, &bios)) { // JP
		for (p = bios+strlen(bios)-1; p > bios && *p != '/'; p--);
		if (*p == '/') p++;
		strncpy(bios_names.jp, p, sizeof(bios_names.jp)); bios_names.jp[sizeof(bios_names.jp)-1] = 0;
	} else	strcpy(bios_names.jp, "NOT FOUND");

	for(;;)
	{
		draw_cd_menu_options(menu_sel, &bios_names);
		inp = in_menu_wait(PBTN_UP|PBTN_DOWN|PBTN_LEFT|PBTN_RIGHT|PBTN_PLAY|PBTN_STOP|PBTN_REW);
		if (inp & PBTN_UP  ) { menu_sel--; if (menu_sel < 0) menu_sel = menu_sel_max; }
		if (inp & PBTN_DOWN) { menu_sel++; if (menu_sel > menu_sel_max) menu_sel = 0; }
		selected_id = me_index2id(cdopt_entries, CDOPT_ENTRY_COUNT, menu_sel);
		if (inp & (PBTN_LEFT|PBTN_RIGHT)) { // multi choise
			if (!me_process(cdopt_entries, CDOPT_ENTRY_COUNT, selected_id, (inp&PBTN_RIGHT) ? 1 : 0) &&
			    selected_id == MA_CDOPT_READAHEAD) {
				if (inp & PBTN_LEFT) {
					PicoCDBuffers >>= 1;
					if (PicoCDBuffers < 2) PicoCDBuffers = 0;
				} else {
					if (PicoCDBuffers < 2) PicoCDBuffers = 2;
					else PicoCDBuffers <<= 1;
					if (PicoCDBuffers > 8*1024) PicoCDBuffers = 8*1024; // 16M
				}
			}
		}
		if (inp & PBTN_PLAY) { // toggleable options
			if (!me_process(cdopt_entries, CDOPT_ENTRY_COUNT, selected_id, 1) &&
			    selected_id == MA_CDOPT_DONE) {
				return;
			}
			switch (selected_id) { // BIOS testers
				case MA_CDOPT_TESTBIOS_USA:
					if (emu_findBios(4, &bios)) { // test US
						strcpy(romFileName, bios);
						engineState = PGS_ReloadRom;
						return;
					}
					break;
				case MA_CDOPT_TESTBIOS_EUR:
					if (emu_findBios(8, &bios)) { // test EU
						strcpy(romFileName, bios);
						engineState = PGS_ReloadRom;
						return;
					}
					break;
				case MA_CDOPT_TESTBIOS_JAP:
					if (emu_findBios(1, &bios)) { // test JP
						strcpy(romFileName, bios);
						engineState = PGS_ReloadRom;
						return;
					}
					break;
				default:
					break;
			}
		}
		if (inp & (PBTN_STOP|PBTN_REW)) return;
	}
}