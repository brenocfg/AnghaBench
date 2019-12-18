#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_9__ ;
typedef  struct TYPE_26__   TYPE_8__ ;
typedef  struct TYPE_25__   TYPE_7__ ;
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_12__ ;
typedef  struct TYPE_18__   TYPE_11__ ;
typedef  struct TYPE_17__   TYPE_10__ ;

/* Type definitions */
struct TYPE_23__ {int screenshot; TYPE_2__* items; TYPE_3__* buttons; int /*<<< orphan*/  cb; TYPE_1__* bg_images; } ;
typedef  TYPE_4__ gui_menu ;
struct TYPE_27__ {int /*<<< orphan*/  state; } ;
struct TYPE_26__ {int /*<<< orphan*/  state; } ;
struct TYPE_25__ {int /*<<< orphan*/  s_device; scalar_t__ bg_overlay; } ;
struct TYPE_24__ {scalar_t__* system; } ;
struct TYPE_22__ {int y; int* shift; int state; } ;
struct TYPE_21__ {int y; void* data; } ;
struct TYPE_20__ {int /*<<< orphan*/  state; } ;
struct TYPE_19__ {int /*<<< orphan*/  state; } ;
struct TYPE_18__ {int /*<<< orphan*/  state; } ;
struct TYPE_17__ {int /*<<< orphan*/  state; } ;
typedef  int /*<<< orphan*/  GXColor ;

/* Variables and functions */
 int AR_SWITCH_ON ; 
 int AR_SWITCH_TRAINER ; 
 int /*<<< orphan*/  BLACK ; 
 int BUTTON_ACTIVE ; 
 int BUTTON_VISIBLE ; 
 void* Button_sm_blue_png ; 
 void* Button_sm_grey_png ; 
 void* Button_sm_yellow_png ; 
 int /*<<< orphan*/  CheatMenu () ; 
 char* DEFAULT_PATH ; 
 int /*<<< orphan*/  GUI_DeleteMenu (TYPE_4__*) ; 
 int /*<<< orphan*/  GUI_DrawMenuFX (TYPE_4__*,int,int) ; 
 int /*<<< orphan*/  GUI_FadeOut () ; 
 int /*<<< orphan*/  GUI_InitMenu (TYPE_4__*) ; 
 int GUI_RunMenu (TYPE_4__*) ; 
 int /*<<< orphan*/  GUI_WaitPrompt (char*,char*) ; 
 int /*<<< orphan*/  IMAGE_VISIBLE ; 
 int /*<<< orphan*/  IO_RESET_HI ; 
 int MAXPATHLEN ; 
 int /*<<< orphan*/  MOUSE_Deinit () ; 
 int /*<<< orphan*/  MOUSE_Init () ; 
 scalar_t__ PAD_ButtonsHeld (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PAD_ScanPads () ; 
 int SYSTEM_MD ; 
 scalar_t__ SYSTEM_MOUSE ; 
 int SYSTEM_SMS ; 
 int /*<<< orphan*/  SYS_POWEROFF ; 
 int /*<<< orphan*/  SYS_ResetSystem (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ Shutdown ; 
 int /*<<< orphan*/  VIDEO_WaitVSync () ; 
 scalar_t__ WPAD_ButtonsHeld (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WPAD_ScanPads () ; 
 scalar_t__ areplay_get_status () ; 
 int /*<<< orphan*/  areplay_set_status (int) ; 
 TYPE_12__* bg_ctrls ; 
 TYPE_11__* bg_list ; 
 TYPE_10__* bg_main ; 
 TYPE_9__* bg_misc ; 
 TYPE_8__* bg_saves ; 
 TYPE_7__ config ; 
 int /*<<< orphan*/  exitmenu () ; 
 int /*<<< orphan*/  gen_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  generic_point_png ; 
 int /*<<< orphan*/  gxClearScreen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gxSaveScreenshot (char*) ; 
 int /*<<< orphan*/  gxSetScreen () ; 
 int /*<<< orphan*/  gxTextureClose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gxTextureOpenPNG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gx_input_FindDevices () ; 
 TYPE_6__ input ; 
 int /*<<< orphan*/ * io_reg ; 
 int /*<<< orphan*/  loadgamemenu () ; 
 int /*<<< orphan*/  mainmenu_cb ; 
 TYPE_4__ menu_main ; 
 int /*<<< orphan*/  optionmenu () ; 
 int /*<<< orphan*/  reloadrom () ; 
 char* rom_filename ; 
 int /*<<< orphan*/  savemenu () ; 
 int /*<<< orphan*/  showrominfo () ; 
 int /*<<< orphan*/  shutdown () ; 
 int /*<<< orphan*/  slot_autoload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slot_autosave (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*) ; 
 int system_hw ; 
 int /*<<< orphan*/  system_init () ; 
 int /*<<< orphan*/  system_reset () ; 
 int /*<<< orphan*/  w_pointer ; 

void mainmenu(void)
{
  char filename[MAXPATHLEN];
  int status, quit = 0;

  /* Autosave Backup RAM */
  slot_autosave(0, config.s_device);

#ifdef HW_RVL
  /* Wiimote shutdown */
  if (Shutdown)
  {
    GUI_FadeOut();
    shutdown();
    SYS_ResetSystem(SYS_POWEROFF, 0, 0);
  }

  /* Wiimote pointer */
  w_pointer = gxTextureOpenPNG(generic_point_png,0);
#endif

  gui_menu *m = &menu_main;

  /* Update main menu */
  if (!m->screenshot)
  {
    if (config.bg_overlay)
    {
      bg_main[1].state  |= IMAGE_VISIBLE;
      bg_misc[1].state  |= IMAGE_VISIBLE;
      bg_ctrls[1].state |= IMAGE_VISIBLE;
      bg_list[1].state  |= IMAGE_VISIBLE;
      bg_saves[2].state |= IMAGE_VISIBLE;
    }
    else
    {
      bg_main[1].state  &= ~IMAGE_VISIBLE;
      bg_misc[1].state  &= ~IMAGE_VISIBLE;
      bg_ctrls[1].state &= ~IMAGE_VISIBLE;
      bg_list[1].state  &= ~IMAGE_VISIBLE;
      bg_saves[2].state &= ~IMAGE_VISIBLE;
    }

    if (system_hw)
    {
      m->screenshot = 128;
      m->bg_images[0].state &= ~IMAGE_VISIBLE;
      m->items[0].y -= 90;
      m->items[1].y -= 90;
      m->items[2].y -= 90;
      m->buttons[0].y -= 90;
      m->buttons[1].y -= 90;
      m->buttons[2].y -= 90;
      m->buttons[0].shift[1] = 3;
      m->buttons[1].shift[1] = 3;
      m->buttons[2].shift[1] = 3;
      m->buttons[3].state |= (BUTTON_VISIBLE | BUTTON_ACTIVE);
      m->buttons[4].state |= (BUTTON_VISIBLE | BUTTON_ACTIVE);
      m->buttons[5].state |= (BUTTON_VISIBLE | BUTTON_ACTIVE);
      m->buttons[7].state |= (BUTTON_VISIBLE | BUTTON_ACTIVE);
      m->buttons[8].state |= (BUTTON_VISIBLE | BUTTON_ACTIVE);
      m->buttons[9].state |= (BUTTON_VISIBLE | BUTTON_ACTIVE);
      if (areplay_get_status() >= 0)
      {
        menu_main.buttons[6].state |= (BUTTON_VISIBLE | BUTTON_ACTIVE);
        menu_main.items[6].data = Button_sm_grey_png;
        menu_main.cb = mainmenu_cb;
        menu_main.buttons[3].shift[1] = 3;
        menu_main.buttons[7].shift[0] = 1;
        menu_main.buttons[8].shift[2] = 2;
      }
    }
  }

  GUI_InitMenu(m);
  GUI_DrawMenuFX(m,10,0);

  while (quit == 0)
  {
    switch (GUI_RunMenu(m))
    {
      /*** Load Game Menu ***/
      case 0:
      {
        GUI_DrawMenuFX(m,30,1);
        GUI_DeleteMenu(m);

        if (loadgamemenu())
        {
          /* restart emulation */
          reloadrom();

          /* check current controller configuration */
          if (!gx_input_FindDevices())
          {
            GUI_InitMenu(m);
            GUI_DrawMenuFX(m,30,0);
            GUI_WaitPrompt("Error","Invalid Controllers Settings");
            break;
          }

          /* exit to game and reinitialize emulation */
          gxClearScreen((GXColor)BLACK);
          gxSetScreen();
          quit = 1;
          break;
        }

        GUI_InitMenu(m);
        GUI_DrawMenuFX(m,30,0);
        break;
      }

      /*** Options Menu */
      case 1:
      {
        GUI_DrawMenuFX(m,30,1);
        GUI_DeleteMenu(m);
        optionmenu();
        GUI_InitMenu(m);
        GUI_DrawMenuFX(m,30,0);
        break;
      }

      /*** Exit Menu ***/
      case 2:
      {
        exitmenu();
        break;
      }

      /*** Save Manager ***/
      case 3:
      {
        GUI_DrawMenuFX(m,30,1);
        GUI_DeleteMenu(m);

        if (savemenu())
        {
          /* check current controller configuration */
          if (!gx_input_FindDevices())
          {
            GUI_InitMenu(m);
            GUI_DrawMenuFX(m,30,0);
            GUI_WaitPrompt("Error","Invalid Controllers Settings");
            break;
          }

          /* exit to game */
          quit = 1;
          break;
        }

        GUI_InitMenu(m);
        GUI_DrawMenuFX(m,30,0);
        break;
      }

      /*** Soft / Hard reset ***/
      case 4:
      {
        /* check current controller configuration */
        if (!gx_input_FindDevices())
        {
          GUI_WaitPrompt("Error","Invalid Controllers Settings");
          break;
        }

        /* reinitialize emulation */
        GUI_DrawMenuFX(m,10,1);
        GUI_DeleteMenu(m);
        gxClearScreen((GXColor)BLACK);
        gxSetScreen();

        if (system_hw & SYSTEM_MD)
        {
          /* Soft Reset */
          gen_reset(0);
        }
        else if (system_hw == SYSTEM_SMS)
        {
          /* assert RESET input (Master System model 1 only) */
          io_reg[0x0D] &= ~IO_RESET_HI;
        }
        else
        {
          /* Hard Reset */
          system_init();
          system_reset();

          /* restore SRAM */
          slot_autoload(0,config.s_device);
        }

        /* exit to game */
        quit = 1;
        break;
      }

      /*** Cheats menu ***/
      case 5:
      {
        GUI_DrawMenuFX(m,30,1);
        GUI_DeleteMenu(m);
        CheatMenu();
        GUI_InitMenu(m);
        GUI_DrawMenuFX(m,30,0);
        break;
      }

      /*** Action Replay switch ***/
      case 6:
      {
        status = (areplay_get_status() + 1) % (AR_SWITCH_TRAINER + 1);
        areplay_set_status(status);
        status = areplay_get_status();
        GUI_DeleteMenu(m);
        if (status == AR_SWITCH_TRAINER) m->items[6].data = Button_sm_blue_png;
        else if (status == AR_SWITCH_ON) m->items[6].data = Button_sm_yellow_png;
        else m->items[6].data = Button_sm_grey_png;
        GUI_InitMenu(m);
        break;
      }

      /*** Return to Game ***/
      case 7:
      case -1:
      {
        if (system_hw)
        {
          /* check current controller configuration */
          if (!gx_input_FindDevices())
          {
            GUI_WaitPrompt("Error","Invalid Controllers Settings");
            break;
          }

          /* exit to game */
          GUI_DrawMenuFX(m,10,1);
          GUI_DeleteMenu(m);
          quit = 1;
        }
        break;
      }

      /*** Game Capture ***/
      case 8:
      {
        /* PNG filename */
        sprintf(filename,"%s/snaps/%s.png", DEFAULT_PATH, rom_filename);

        /* Save file and return */
        gxSaveScreenshot(filename);
        break;
      }

      /*** ROM information screen ***/
      case 9:
      {
        showrominfo();
        break;
      }
    }
  }

  /*** Remove any still held buttons ***/
  while (PAD_ButtonsHeld(0))
  {
    VIDEO_WaitVSync();
    PAD_ScanPads();
  }
#ifdef HW_RVL
  while (WPAD_ButtonsHeld(0)) 
  {
    VIDEO_WaitVSync();
    WPAD_ScanPads();
  }
  gxTextureClose(&w_pointer);

  /* USB Mouse support */
  if ((input.system[0] == SYSTEM_MOUSE) || (input.system[1] == SYSTEM_MOUSE))
  {
    MOUSE_Init();
  }
  else
  {
    MOUSE_Deinit();
  }
#endif
}