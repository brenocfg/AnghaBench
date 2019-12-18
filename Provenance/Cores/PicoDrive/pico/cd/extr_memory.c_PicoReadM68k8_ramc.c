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
struct TYPE_5__ {int* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  EL_UIO ; 
 TYPE_3__* Pico_mcd ; 
 TYPE_2__ SRam ; 
 int /*<<< orphan*/  SekPc ; 
 int /*<<< orphan*/  elprintf (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 PicoReadM68k8_ramc(u32 a)
{
  u32 d = 0;
  if (a == 0x400001) {
    if (SRam.data != NULL)
      d = 3; // 64k cart
    return d;
  }

  if ((a & 0xfe0000) == 0x600000) {
    if (SRam.data != NULL)
      d = SRam.data[((a >> 1) & 0xffff) + 0x2000];
    return d;
  }

  if (a == 0x7fffff)
    return Pico_mcd->m.bcram_reg;

  elprintf(EL_UIO, "m68k unmapped r8  [%06x] @%06x", a, SekPc);
  return d;
}