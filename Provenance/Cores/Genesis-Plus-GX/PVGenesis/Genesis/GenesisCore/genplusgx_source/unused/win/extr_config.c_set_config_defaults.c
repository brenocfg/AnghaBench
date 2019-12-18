#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int psg_preamp; int fm_preamp; int hq_fm; int filter; int low_freq; int high_freq; double lg; double mg; double hg; int lp_range; double rolloff; int dac_bits; int addr_error; int overscan; int* gun_cursor; TYPE_1__* input; scalar_t__ invert_mouse; scalar_t__ render; scalar_t__ romtype; scalar_t__ lock_on; scalar_t__ tmss; scalar_t__ force_dtack; scalar_t__ region_detect; scalar_t__ psgBoostNoise; } ;
struct TYPE_5__ {void** system; } ;
struct TYPE_4__ {int /*<<< orphan*/  padtype; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVICE_PAD6B ; 
 int MAX_INPUTS ; 
 void* SYSTEM_MD_GAMEPAD ; 
 TYPE_3__ config ; 
 TYPE_2__ input ; 

void set_config_defaults(void)
{
  int i;

  /* sound options */
  config.psg_preamp     = 150;
  config.fm_preamp      = 100;
  config.hq_fm          = 1;
  config.psgBoostNoise  = 0;
  config.filter         = 1;
  config.low_freq       = 200;
  config.high_freq      = 8000;
  config.lg             = 1.0;
  config.mg             = 1.0;
  config.hg             = 1.0;
  config.lp_range       = 60;
  config.rolloff        = 0.995;
  config.dac_bits       = 14;

  /* system options */
  config.region_detect  = 0;
  config.force_dtack    = 0;
  config.addr_error     = 1;
  config.tmss           = 0;
  config.lock_on        = 0;//TYPE_SK;
  config.romtype        = 0;

  /* display options */
  config.overscan = 1;
  config.render   = 0;

  /* controllers options */
  input.system[0]       = SYSTEM_MD_GAMEPAD;
  input.system[1]       = SYSTEM_MD_GAMEPAD;
  config.gun_cursor[0]  = 1;
  config.gun_cursor[1]  = 1;
  config.invert_mouse   = 0;
  for (i=0;i<MAX_INPUTS;i++)
  {
    config.input[i].padtype = DEVICE_PAD6B;
  }
}