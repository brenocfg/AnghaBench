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
typedef  int u16 ;
struct TYPE_3__ {int /*<<< orphan*/  emu_status; } ;
struct TYPE_4__ {scalar_t__ dram; TYPE_1__ ssp1601; } ;

/* Variables and functions */
 int /*<<< orphan*/  SSP_WAIT_30FE06 ; 
 int /*<<< orphan*/  SSP_WAIT_30FE08 ; 
 TYPE_2__* svp ; 

__attribute__((used)) static void PicoWrite16_dram(u32 a, u32 d)
{
  a &= ~0xfe0000;

  if (d != 0) {
    if      (a == 0xfe06) // 30fe06
      svp->ssp1601.emu_status &= ~SSP_WAIT_30FE06;
    else if (a == 0xfe08)
      svp->ssp1601.emu_status &= ~SSP_WAIT_30FE08;
  }

  ((u16 *)svp->dram)[a / 2] = d;
}