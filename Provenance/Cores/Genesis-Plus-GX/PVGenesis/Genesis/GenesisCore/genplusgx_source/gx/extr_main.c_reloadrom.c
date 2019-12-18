#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ status; } ;
struct TYPE_7__ {int hot_swap; int /*<<< orphan*/  s_device; int /*<<< orphan*/  s_default; } ;
struct TYPE_5__ {scalar_t__ boot; } ;
struct TYPE_6__ {TYPE_1__ cartridge; } ;

/* Variables and functions */
 scalar_t__ CD_OPEN ; 
 int /*<<< orphan*/  CheatLoad () ; 
 int /*<<< orphan*/  SAMPLERATE_48KHZ ; 
 int SYSTEM_MCD ; 
 int SYSTEM_MD ; 
 int SYSTEM_PBC ; 
 int /*<<< orphan*/  audio_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__ cdd ; 
 TYPE_3__ config ; 
 int /*<<< orphan*/  get_framerate () ; 
 scalar_t__ interlaced ; 
 int /*<<< orphan*/  md_cart_init () ; 
 int /*<<< orphan*/  md_cart_reset (int) ; 
 TYPE_2__ scd ; 
 int /*<<< orphan*/  slot_autoload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sms_cart_init () ; 
 int /*<<< orphan*/  sms_cart_reset () ; 
 int system_hw ; 
 int /*<<< orphan*/  system_init () ; 
 int /*<<< orphan*/  system_reset () ; 

void reloadrom(void)
{
  /* Cartridge "Hot Swap" support (make sure system has already been inited once and use cartridges) */
  if ((config.hot_swap == 3) && ((system_hw != SYSTEM_MCD) || scd.cartridge.boot))
  {
    /* Only initialize cartridge hardware */
    if ((system_hw & SYSTEM_PBC) == SYSTEM_MD)
    {
      /* 16-bit cartridge */
      md_cart_init();
      md_cart_reset(1);
    }
    else
    {
      /* 8-bit cartridge */
      sms_cart_init();
      sms_cart_reset();
    }
  }

  /* Disc Swap support (automatically enabled if CD tray is open) */
  else if ((system_hw != SYSTEM_MCD) || (cdd.status != CD_OPEN))
  {
    /* Initialize audio emulation */
    interlaced = 0;
    audio_init(SAMPLERATE_48KHZ, get_framerate());
     
    /* Switch virtual system on */
    system_init();
    system_reset();

    /* Allow hot swap */
    config.hot_swap |= 2;
  }

  /* Auto-Load Backup RAM */
  slot_autoload(0,config.s_device);
            
  /* Auto-Load State */
  slot_autoload(config.s_default,config.s_device);

  /* Load Cheat file */
  CheatLoad();
}