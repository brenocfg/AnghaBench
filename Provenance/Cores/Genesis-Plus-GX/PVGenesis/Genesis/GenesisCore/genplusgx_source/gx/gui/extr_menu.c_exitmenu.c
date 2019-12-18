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
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  GUI_DeleteMenu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GUI_FadeOut () ; 
 int /*<<< orphan*/  GUI_InitMenu (int /*<<< orphan*/ *) ; 
 int GUI_OptionWindow (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**,int) ; 
 int /*<<< orphan*/  SYS_HOTRESET ; 
 int /*<<< orphan*/  SYS_RETURNTOMENU ; 
 int /*<<< orphan*/  SYS_ResetSystem (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYS_SHUTDOWN ; 
 int /*<<< orphan*/  __lwp_thread_stopmultitasking (void (*) ()) ; 
 int /*<<< orphan*/  gxTextureClose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  menu_main ; 
 int /*<<< orphan*/  osd_version ; 
 int /*<<< orphan*/  showcredits () ; 
 int /*<<< orphan*/  shutdown () ; 
 int /*<<< orphan*/  w_pointer ; 

__attribute__((used)) static void exitmenu(void)
{
  char *items[3] =
  {
    "View Credits",
#ifdef HW_RVL
    "Exit to System Menu",
#else
    "Reset System",
#endif
    "Return to Loader",
  };

  /* autodetect loader stub */
  int maxitems = 2;
  u32 *sig = (u32*)0x80001800;
  void (*reload)() = (void(*)())0x80001800;

#ifdef HW_RVL
  if ((sig[1] == 0x53545542) && (sig[2] == 0x48415858)) // HBC
#else
  if (sig[0] == 0x7c6000a6) // SDLOAD
#endif
  {
    maxitems = 3;
  }

  /* display option window */
  switch (GUI_OptionWindow(&menu_main, osd_version, items, maxitems))
  {
    case 0: /* credits */
      GUI_DeleteMenu(&menu_main);
      showcredits();
      GUI_InitMenu(&menu_main);
      break;

    case 1: /* reset */
#ifdef HW_RVL
      gxTextureClose(&w_pointer);
#endif
      GUI_DeleteMenu(&menu_main);
      GUI_FadeOut();
      shutdown();
#ifdef HW_RVL
      SYS_ResetSystem(SYS_RETURNTOMENU, 0, 0);
#else
      SYS_ResetSystem(SYS_HOTRESET,0,0);
#endif
      break;

    case 2: /* exit to loader */
#ifdef HW_RVL
      gxTextureClose(&w_pointer);
#endif
      GUI_DeleteMenu(&menu_main);
      GUI_FadeOut();
      shutdown();
      SYS_ResetSystem(SYS_SHUTDOWN,0,0);
      __lwp_thread_stopmultitasking(*reload);
      break;

    default:
      break;
  }
}