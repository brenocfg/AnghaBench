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
struct TYPE_2__ {int tv_mode; scalar_t__ render; int /*<<< orphan*/  vsync; } ;

/* Variables and functions */
 TYPE_1__ config ; 
 scalar_t__ interlaced ; 
 scalar_t__ vdp_pal ; 

double get_framerate(void)
{
  /* Run emulator at original VDP framerate if console TV mode does not match emulated TV mode or VSYNC is disabled */
  if (!config.vsync || (config.tv_mode == !vdp_pal))
  {
    return 0.0;
  }

  /* Otherwise, run emulator at Wii/Gamecube framerate to ensure perfect video synchronization */
  if (vdp_pal)
  {
    /* 288p      -> 13500000 pixels/sec, 864 pixels/line, 312 lines/field -> fps = 13500000/864/312 = 50.08 hz */
    /* 288i,576i -> 13500000 pixels/sec, 864 pixels/line, 312.5 lines/field (two fields = one frame = 625 lines) -> fps = 13500000/864/312.5 = 50.00 hz */
    return (config.render || interlaced) ? (27000000.0/864.0/625.0) : (13500000.0/864.0/312.0);
  }
  else
  {
    /* 240p      -> 13500000 pixels/sec, 858 pixels/line, 263 lines/field -> fps = 13500000/858/263 = 59.83 hz */
    /* 240i,480i -> 13500000 pixels/sec, 858 pixels/line, 262.5 lines/field (two fields = one frame = 525 lines) -> fps = 13500000/858/262.5 = 59.94 hz */
    /* 480p      -> 27000000 pixels/sec, 858 pixels/line, 525 lines/field -> fps = 27000000/858/525 = 59.94 hz */
    return (config.render || interlaced) ? (27000000.0/858.0/525.0) : (13500000.0/858.0/263.0);
  }
}