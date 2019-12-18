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
typedef  int /*<<< orphan*/  cd_img_type ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  CIT_NOT_CD ; 
 int Framework_PollGetButtons () ; 
 int Insert_CD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MAX_PATH ; 
 int PBTN_DOWN ; 
 int PBTN_PLAY ; 
 int PBTN_UP ; 
 int /*<<< orphan*/  PGS_RestartRun ; 
 int /*<<< orphan*/  Sleep (int) ; 
 int /*<<< orphan*/  draw_menu_tray (int) ; 
 int /*<<< orphan*/  emu_cdCheck (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  engineState ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  getcwd (char*,int) ; 
 unsigned long in_menu_wait (int) ; 
 int /*<<< orphan*/  loadedRomFName ; 
 int /*<<< orphan*/  lprintf (char*,scalar_t__*) ; 
 scalar_t__* menuErrorMsg ; 
 int /*<<< orphan*/  menu_gfx_prepare () ; 
 int /*<<< orphan*/  romFileName ; 
 char* romsel_loop (char*) ; 
 int /*<<< orphan*/  sprintf (scalar_t__*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 

int menu_loop_tray(void)
{
	int menu_sel = 0, menu_sel_max = 1;
	unsigned long inp = 0;
	char curr_path[MAX_PATH], *selfname;
	FILE *tstf;

	menu_gfx_prepare();

	if ( (tstf = fopen(loadedRomFName, "rb")) )
	{
		fclose(tstf);
		strcpy(curr_path, loadedRomFName);
	}
	else
	{
		getcwd(curr_path, MAX_PATH);
	}

	/* make sure action buttons are not pressed on entering menu */
	draw_menu_tray(menu_sel);
	while (Framework_PollGetButtons() & PBTN_PLAY) Sleep(50);

	for (;;)
	{
		draw_menu_tray(menu_sel);
		inp = in_menu_wait(PBTN_UP|PBTN_DOWN|PBTN_PLAY);
		if(inp & PBTN_UP  )  { menu_sel--; if (menu_sel < 0) menu_sel = menu_sel_max; }
		if(inp & PBTN_DOWN)  { menu_sel++; if (menu_sel > menu_sel_max) menu_sel = 0; }
		if(inp & PBTN_PLAY)  {
			switch (menu_sel) {
				case 0: // select image
					selfname = romsel_loop(curr_path);
					if (selfname) {
						int ret = -1;
						cd_img_type cd_type;
						cd_type = emu_cdCheck(NULL, romFileName);
						if (cd_type != CIT_NOT_CD)
							ret = Insert_CD(romFileName, cd_type);
						if (ret != 0) {
							sprintf(menuErrorMsg, "Load failed, invalid CD image?");
							lprintf("%s\n", menuErrorMsg);
							continue;
						}
						engineState = PGS_RestartRun;
						return 1;
					}
					break;
				case 1: // insert nothing
					engineState = PGS_RestartRun;
					return 0;
			}
		}
		menuErrorMsg[0] = 0; // clear error msg
	}
}