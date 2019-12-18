#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {unsigned int cycles; } ;
struct TYPE_8__ {scalar_t__ cycle; } ;
struct TYPE_13__ {TYPE_1__ poll; } ;
struct TYPE_9__ {scalar_t__ cycle; } ;
struct TYPE_12__ {unsigned int cycles; TYPE_2__ poll; } ;
struct TYPE_11__ {unsigned int stopwatch; TYPE_3__* regs; } ;
struct TYPE_10__ {int w; } ;

/* Variables and functions */
 unsigned int TIMERS_SCYCLES_RATIO ; 
 TYPE_7__ gfx ; 
 TYPE_6__ m68k ; 
 TYPE_5__ s68k ; 
 TYPE_4__ scd ; 

void scd_end_frame(unsigned int cycles)
{
  /* run Stopwatch until end of frame */
  int ticks = (cycles - scd.stopwatch) / TIMERS_SCYCLES_RATIO;
  scd.regs[0x0c>>1].w = (scd.regs[0x0c>>1].w + ticks) & 0xfff;

  /* adjust Stopwatch counter for next frame (can be negative) */
  scd.stopwatch += (ticks * TIMERS_SCYCLES_RATIO) - cycles;

  /* adjust SUB-CPU & GPU cycle counters for next frame */
  s68k.cycles -= cycles;
  gfx.cycles  -= cycles;

  /* reset CPU registers polling */
  m68k.poll.cycle = 0;
  s68k.poll.cycle = 0;
}