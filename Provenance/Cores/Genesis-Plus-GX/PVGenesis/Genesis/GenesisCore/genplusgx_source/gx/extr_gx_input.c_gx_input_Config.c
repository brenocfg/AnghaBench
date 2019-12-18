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
typedef  int u8 ;
struct TYPE_2__ {int /*<<< orphan*/ * system; } ;

/* Variables and functions */
#define  DEVICE_LIGHTGUN 137 
#define  DEVICE_MOUSE 136 
#define  DEVICE_PAD2B 135 
#define  DEVICE_PAD3B 134 
#define  DEVICE_PAD6B 133 
#define  DEVICE_PADDLE 132 
#define  DEVICE_PICO 131 
#define  DEVICE_SPORTSPAD 130 
#define  DEVICE_TEREBI 129 
#define  DEVICE_XE_A1P 128 
 int /*<<< orphan*/  GUI_WaitPrompt (char*,char*) ; 
 size_t KEY_BUTTONA ; 
 size_t KEY_BUTTONB ; 
 size_t KEY_BUTTONC ; 
 size_t KEY_BUTTONX ; 
 size_t KEY_BUTTONY ; 
 size_t KEY_BUTTONZ ; 
 size_t KEY_MODE ; 
 size_t KEY_START ; 
 int /*<<< orphan*/  SYSTEM_JUSTIFIER ; 
 int /*<<< orphan*/  SYSTEM_MENACER ; 
 TYPE_1__ input ; 
 int /*<<< orphan*/ * keyname ; 
 int /*<<< orphan*/  pad_config (int,int,int) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpad_config (int,int,int,int) ; 

void gx_input_Config(u8 chan, u8 device, u8 type)
{
  int first_key, last_key;

  /* emulated device */
  switch (type)
  {
    case DEVICE_PADDLE:
    case DEVICE_PAD2B:
    case DEVICE_SPORTSPAD:
    {
      first_key = KEY_BUTTONB;
      last_key = KEY_START;
      sprintf(keyname[KEY_BUTTONB],"Button 1");
      sprintf(keyname[KEY_BUTTONC],"Button 2");
      sprintf(keyname[KEY_START],"PAUSE Button");
      break;
    }

    case DEVICE_XE_A1P:
    {
      first_key = KEY_BUTTONA;
      last_key = KEY_MODE;
      sprintf(keyname[KEY_BUTTONA],"Button A");
      sprintf(keyname[KEY_BUTTONB],"Button B");
      sprintf(keyname[KEY_BUTTONC],"Button C");
      sprintf(keyname[KEY_START],"START Button");
      sprintf(keyname[KEY_BUTTONX],"Button D");
      sprintf(keyname[KEY_BUTTONY],"Button E1");
      sprintf(keyname[KEY_BUTTONZ],"Button E2");
      sprintf(keyname[KEY_MODE],"SELECT Button");
      break;
    }

    case DEVICE_MOUSE:
    {
      first_key = KEY_BUTTONA;
      last_key = KEY_START;
      sprintf(keyname[KEY_BUTTONA],"Middle Button");
      sprintf(keyname[KEY_BUTTONB],"Left Button");
      sprintf(keyname[KEY_BUTTONC],"Right Button");
      sprintf(keyname[KEY_START],"START Button");
      break;
    }

    case DEVICE_PAD3B:
    {
      first_key = KEY_BUTTONA;
      last_key = KEY_START;
      sprintf(keyname[KEY_BUTTONA],"Button A");
      sprintf(keyname[KEY_BUTTONB],"Button B");
      sprintf(keyname[KEY_BUTTONC],"Button C");
      sprintf(keyname[KEY_START],"START Button");
      break;
    }

    case DEVICE_PAD6B:
    {
      first_key = KEY_BUTTONA;
      last_key = KEY_MODE;
      sprintf(keyname[KEY_BUTTONA],"Button A");
      sprintf(keyname[KEY_BUTTONB],"Button B");
      sprintf(keyname[KEY_BUTTONC],"Button C");
      sprintf(keyname[KEY_START],"START Button");
      sprintf(keyname[KEY_BUTTONX],"Button X");
      sprintf(keyname[KEY_BUTTONY],"Button Y");
      sprintf(keyname[KEY_BUTTONZ],"Button Z");
      sprintf(keyname[KEY_MODE],"MODE Button");
      break;
    }

    case DEVICE_LIGHTGUN:
    {
      first_key = KEY_BUTTONA;
      last_key = KEY_START;
      if (input.system[1] == SYSTEM_MENACER)
      {
        sprintf(keyname[KEY_BUTTONA],"TRIGGER Button");
        sprintf(keyname[KEY_BUTTONB],"Button B");
        sprintf(keyname[KEY_BUTTONC],"Button C");
        sprintf(keyname[KEY_START],"START Button");
      }
      else if (input.system[1] == SYSTEM_JUSTIFIER)
      {
        sprintf(keyname[KEY_BUTTONA],"TRIGGER Button");
        sprintf(keyname[KEY_BUTTONB],"N.A");
        sprintf(keyname[KEY_BUTTONC],"N.A");
        sprintf(keyname[KEY_START],"START Button");
      }
      else
      {
        sprintf(keyname[KEY_BUTTONA],"TRIGGER Button");
        sprintf(keyname[KEY_BUTTONB],"N.A");
        sprintf(keyname[KEY_BUTTONC],"N.A");
        sprintf(keyname[KEY_START],"PAUSE Button");
      }
      break;
    }

    case DEVICE_PICO:
    {
      first_key = KEY_BUTTONA;
      last_key = KEY_BUTTONB;
      sprintf(keyname[KEY_BUTTONA],"PEN Button");
      sprintf(keyname[KEY_BUTTONB],"RED Button");
      break;
    }

    case DEVICE_TEREBI:
    {
      first_key = KEY_BUTTONA;
      last_key = KEY_BUTTONA;
      sprintf(keyname[KEY_BUTTONA],"PEN Button");
      break;
    }

    default:
    {
      first_key = KEY_BUTTONA;
      last_key = KEY_BUTTONA;
      sprintf(keyname[KEY_BUTTONA],"N.A");
      GUI_WaitPrompt("Info","Activator is not configurable !");
      break;
    }
  }

  /* Input device */
  switch (device)
  {
    case 0:
    {
      pad_config(chan, first_key, last_key);
      break;
    }

    default:
    {
#ifdef HW_RVL
      wpad_config(device - 1, chan, first_key, last_key);
#endif
      break;
    }
  }
}