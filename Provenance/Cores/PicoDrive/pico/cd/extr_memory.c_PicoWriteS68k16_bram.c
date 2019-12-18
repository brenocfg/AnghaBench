#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {int* bram; } ;
struct TYPE_3__ {int changed; } ;

/* Variables and functions */
 int /*<<< orphan*/  EL_ANOMALY ; 
 TYPE_2__* Pico_mcd ; 
 TYPE_1__ SRam ; 
 int /*<<< orphan*/  SekPcS68k ; 
 int /*<<< orphan*/  elprintf (int /*<<< orphan*/ ,char*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void PicoWriteS68k16_bram(u32 a, u32 d)
{
  elprintf(EL_ANOMALY, "s68k_bram w16: [%06x] %04x @%06x", a, d, SekPcS68k);
  a = (a >> 1) & 0x1fff;
  Pico_mcd->bram[a++] = d;
  Pico_mcd->bram[a++] = d >> 8; // TODO: verify..
  SRam.changed = 1;
}