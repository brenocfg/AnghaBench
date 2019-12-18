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
typedef  int u32 ;
struct TYPE_2__ {int fifo_bytes; } ;

/* Variables and functions */
 int /*<<< orphan*/  EL_UIO ; 
 TYPE_1__ PicoPicohw ; 
 int /*<<< orphan*/  SekPc ; 
 int /*<<< orphan*/  elprintf (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 PicoRead16_pico(u32 a)
{
  u32 d = 0;

  if      (a == 0x800010)
    d = (PicoPicohw.fifo_bytes > 0x3f) ? 0 : (0x3f - PicoPicohw.fifo_bytes);
  else if (a == 0x800012)
    d = PicoPicohw.fifo_bytes == 0 ? 0x8000 : 0; // guess
  else
    elprintf(EL_UIO, "m68k unmapped r16 [%06x] @%06x", a, SekPc);

  return d;
}