#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  gui_menu ;
struct TYPE_2__ {int /*<<< orphan*/  l_device; } ;

/* Variables and functions */
 int /*<<< orphan*/  FileSelector (int) ; 
 int /*<<< orphan*/  GUI_DeleteMenu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GUI_DrawMenuFX (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  GUI_InitMenu (int /*<<< orphan*/ *) ; 
 int GUI_RunMenu (int /*<<< orphan*/ *) ; 
 int OpenDirectory (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TYPE_RECENT ; 
 TYPE_1__ config ; 
 int /*<<< orphan*/  menu_load ; 

__attribute__((used)) static int loadgamemenu ()
{
  int ret, filetype;
  gui_menu *m = &menu_load;
  GUI_InitMenu(m);
  GUI_DrawMenuFX(m,30,0);

  while (1)
  {
    ret = GUI_RunMenu(m);

    switch (ret)
    {
      /*** Button B ***/
      case -1: 
        GUI_DrawMenuFX(m,30,1);
        GUI_DeleteMenu(m);
        return 0;

      /*** Load from selected device */
      default:
      {
        /* ROM File type */
        filetype = ret - 1;

        /* Try to open current directory */
        if (ret > 0)
        {
          ret = OpenDirectory(config.l_device, filetype);
        }
        else
        {
          ret = OpenDirectory(TYPE_RECENT, filetype);
        }

        if (ret)
        {
          GUI_DeleteMenu(m);
          if (FileSelector(filetype))
          {
            /* directly jump to game */
            return 1;
          }
          GUI_InitMenu(m);
        }
        break;
      }
    }
  }

  return 0;
}