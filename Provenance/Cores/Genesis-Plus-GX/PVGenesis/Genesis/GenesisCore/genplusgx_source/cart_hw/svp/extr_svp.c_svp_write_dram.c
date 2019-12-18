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
typedef  int uint32 ;
typedef  int uint16 ;
struct TYPE_3__ {int /*<<< orphan*/  emu_status; } ;
struct TYPE_4__ {TYPE_1__ ssp1601; scalar_t__ dram; } ;

/* Variables and functions */
 int /*<<< orphan*/  SSP_WAIT_30FE06 ; 
 int /*<<< orphan*/  SSP_WAIT_30FE08 ; 
 TYPE_2__* svp ; 

void svp_write_dram(uint32 address, uint32 data)
{
  *(uint16 *)(svp->dram + (address & 0x1fffe)) = data;
  if ((address == 0x30fe06) && data) svp->ssp1601.emu_status &= ~SSP_WAIT_30FE06;
  if ((address == 0x30fe08) && data) svp->ssp1601.emu_status &= ~SSP_WAIT_30FE08;
}