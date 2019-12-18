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
struct TYPE_2__ {int* bram; } ;

/* Variables and functions */
 int /*<<< orphan*/  EL_ANOMALY ; 
 TYPE_1__* Pico_mcd ; 
 int /*<<< orphan*/  SekPcS68k ; 
 int /*<<< orphan*/  elprintf (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 PicoReadS68k16_bram(u32 a)
{
  u32 d;
  elprintf(EL_ANOMALY, "FIXME: s68k_bram r16: [%06x] @%06x", a, SekPcS68k);
  a = (a >> 1) & 0x1fff;
  d = Pico_mcd->bram[a++];
  d|= Pico_mcd->bram[a++] << 8; // probably wrong, TODO: verify
  return d;
}