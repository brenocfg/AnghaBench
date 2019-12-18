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
struct TYPE_2__ {int psg_preamp; int fm_preamp; int hq_fm; int psgBoostNoise; int lp_range; int low_freq; int high_freq; double lg; double mg; double hg; int dac_bits; int ym2413; int addr_error; int ntsc; scalar_t__ render; scalar_t__ gg_extra; scalar_t__ overscan; scalar_t__ hot_swap; scalar_t__ lock_on; scalar_t__ bios; scalar_t__ force_dtack; scalar_t__ master_clock; scalar_t__ vdp_mode; scalar_t__ region_detect; scalar_t__ system; scalar_t__ mono; scalar_t__ filter; int /*<<< orphan*/  version; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_VERSION ; 
 TYPE_1__ config ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void config_default(void)
{
   /* version TAG */
   strncpy(config.version,CONFIG_VERSION,16);

   /* sound options */
   config.psg_preamp     = 150;
   config.fm_preamp      = 100;
   config.hq_fm          = 1;
   config.psgBoostNoise  = 1;
   config.filter         = 0;
   config.lp_range       = 0x9999; /* 0.6 in 16.16 fixed point */
   config.low_freq       = 880;
   config.high_freq      = 5000;
   config.lg             = 1.0;
   config.mg             = 1.0;
   config.hg             = 1.0;
   config.dac_bits 	 = 14;
   config.ym2413         = 2; /* AUTO */
   config.mono           = 0;

   /* system options */
   config.system         = 0; /* AUTO */
   config.region_detect  = 0; /* AUTO */
   config.vdp_mode       = 0; /* AUTO */
   config.master_clock   = 0; /* AUTO */
   config.force_dtack    = 0;
   config.addr_error     = 1;
   config.bios           = 0;
   config.lock_on        = 0;
   config.hot_swap       = 0;

   /* video options */
   config.overscan = 0; /* 3 == FULL */
   config.gg_extra = 0; /* 1 = show extended Game Gear screen (256x192) */
#if defined(USE_NTSC)
   config.ntsc     = 1;
#endif

   config.render   = 0;
}