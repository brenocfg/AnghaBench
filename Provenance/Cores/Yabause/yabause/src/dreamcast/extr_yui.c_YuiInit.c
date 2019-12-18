#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int sh2coretype; scalar_t__ skip_load; scalar_t__ basetime; scalar_t__ clocksync; int /*<<< orphan*/  videoformattype; scalar_t__ frameskip; int /*<<< orphan*/ * cartpath; int /*<<< orphan*/ * mpegpath; int /*<<< orphan*/ * buppath; int /*<<< orphan*/ * cdpath; int /*<<< orphan*/ * biospath; int /*<<< orphan*/  regionid; int /*<<< orphan*/  carttype; int /*<<< orphan*/  cdcoretype; int /*<<< orphan*/  sndcoretype; int /*<<< orphan*/  m68kcoretype; int /*<<< orphan*/  vidcoretype; int /*<<< orphan*/  percoretype; } ;
typedef  TYPE_1__ yabauseinit_struct ;
struct TYPE_5__ {int /*<<< orphan*/  (* HandleEvents ) () ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CART_NONE ; 
 int /*<<< orphan*/  CDCORE_ARCH ; 
 int /*<<< orphan*/  M68KCORE_C68K ; 
 int /*<<< orphan*/  PERCORE_DC ; 
 TYPE_3__* PERCore ; 
 int /*<<< orphan*/  REGION_AUTODETECT ; 
 int /*<<< orphan*/  SNDCORE_DUMMY ; 
 int /*<<< orphan*/  VIDCORE_DC ; 
 int /*<<< orphan*/  VIDEOFORMATTYPE_NTSC ; 
 scalar_t__ YabauseInit (TYPE_1__*) ; 
 int /*<<< orphan*/ * bios ; 
 scalar_t__ emulate_bios ; 
 int /*<<< orphan*/  stub1 () ; 

int YuiInit(int sh2core)   {
    yabauseinit_struct yinit;

    yinit.percoretype = PERCORE_DC;
    yinit.sh2coretype = sh2core;
    yinit.vidcoretype = VIDCORE_DC;
    yinit.m68kcoretype = M68KCORE_C68K;
    yinit.sndcoretype = SNDCORE_DUMMY;
    yinit.cdcoretype = CDCORE_ARCH;
    yinit.carttype = CART_NONE;
    yinit.regionid = REGION_AUTODETECT;
    yinit.biospath = emulate_bios ? NULL : bios;
    yinit.cdpath = NULL;
    yinit.buppath = NULL;
    yinit.mpegpath = NULL;
    yinit.cartpath = NULL;
    yinit.frameskip = 0;
    yinit.videoformattype = VIDEOFORMATTYPE_NTSC;
    yinit.clocksync = 0;
    yinit.basetime = 0;
    yinit.skip_load = 0;

    if(YabauseInit(&yinit) != 0)
      return -1;

    for(;;) {
        PERCore->HandleEvents();
    }

    return 0;
}