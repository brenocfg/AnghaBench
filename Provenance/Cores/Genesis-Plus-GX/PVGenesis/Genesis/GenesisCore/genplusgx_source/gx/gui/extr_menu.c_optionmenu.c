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
typedef  int /*<<< orphan*/  gui_menu ;

/* Variables and functions */
 int /*<<< orphan*/  GUI_DeleteMenu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GUI_DrawMenuFX (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  GUI_InitMenu (int /*<<< orphan*/ *) ; 
 int GUI_RunMenu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  config_save () ; 
 int /*<<< orphan*/  ctrlmenu () ; 
 int /*<<< orphan*/  menu_options ; 
 int /*<<< orphan*/  prefmenu () ; 
 int /*<<< orphan*/  soundmenu () ; 
 int /*<<< orphan*/  systemmenu () ; 
 int /*<<< orphan*/  videomenu () ; 

__attribute__((used)) static void optionmenu(void)
{
  int ret, quit = 0;
  gui_menu *m = &menu_options;

  GUI_InitMenu(m);
  GUI_DrawMenuFX(m,30,0);

  while (quit == 0)
  {
    ret = GUI_RunMenu(m);

    switch (ret)
    {
      case 0:
        GUI_DeleteMenu(m);
        systemmenu();
        GUI_InitMenu(m);
        break;
      case 1:
        GUI_DeleteMenu(m);
        videomenu();
        GUI_InitMenu(m);
        break;
      case 2:
        GUI_DeleteMenu(m);
        soundmenu();
        GUI_InitMenu(m);
        break;
      case 3:
        GUI_DeleteMenu(m);
        ctrlmenu();
        GUI_InitMenu(m);
        break;
      case 4:
        GUI_DeleteMenu(m);
        prefmenu();
        GUI_InitMenu(m);
        break;
      case -1:
        quit = 1;
        break;
    }
  }

  config_save();
  GUI_DrawMenuFX(m,30,1);
  GUI_DeleteMenu(m);
}