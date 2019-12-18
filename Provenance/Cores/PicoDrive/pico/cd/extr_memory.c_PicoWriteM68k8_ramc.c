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
typedef  int u32 ;
struct TYPE_4__ {int bcram_reg; } ;
struct TYPE_6__ {TYPE_1__ m; } ;
struct TYPE_5__ {int* data; int changed; } ;

/* Variables and functions */
 int /*<<< orphan*/  EL_UIO ; 
 TYPE_3__* Pico_mcd ; 
 TYPE_2__ SRam ; 
 int /*<<< orphan*/  SekPc ; 
 int /*<<< orphan*/  elprintf (int /*<<< orphan*/ ,char*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void PicoWriteM68k8_ramc(u32 a, u32 d)
{
  if ((a & 0xfe0000) == 0x600000) {
    if (SRam.data != NULL && (Pico_mcd->m.bcram_reg & 1)) {
      SRam.data[((a>>1) & 0xffff) + 0x2000] = d;
      SRam.changed = 1;
    }
    return;
  }

  if (a == 0x7fffff) {
    Pico_mcd->m.bcram_reg = d;
    return;
  }

  elprintf(EL_UIO, "m68k unmapped w8  [%06x]   %02x @%06x",
    a, d & 0xff, SekPc);
}