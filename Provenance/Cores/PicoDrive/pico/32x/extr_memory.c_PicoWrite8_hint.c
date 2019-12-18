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
struct TYPE_2__ {int* m68k_rom; } ;

/* Variables and functions */
 int /*<<< orphan*/  EL_UIO ; 
 TYPE_1__* Pico32xMem ; 
 int /*<<< orphan*/  SekPc ; 
 int /*<<< orphan*/  elprintf (int /*<<< orphan*/ ,char*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void PicoWrite8_hint(u32 a, u32 d)
{
  if ((a & 0xfffc) == 0x0070) {
    Pico32xMem->m68k_rom[a ^ 1] = d;
    return;
  }

  elprintf(EL_UIO, "m68k unmapped w8  [%06x]   %02x @%06x",
    a, d & 0xff, SekPc);
}