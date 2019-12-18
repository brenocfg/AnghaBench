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
struct TYPE_4__ {scalar_t__ rom; } ;
struct TYPE_3__ {int /*<<< orphan*/  ssp1601; scalar_t__ iram_rom; } ;

/* Variables and functions */
 TYPE_2__ cart ; 
 int /*<<< orphan*/  memcpy (scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  ssp1601_reset (int /*<<< orphan*/ *) ; 
 TYPE_1__* svp ; 

void svp_reset(void)
{
  memcpy(svp->iram_rom + 0x800, cart.rom + 0x800, 0x20000 - 0x800);
  ssp1601_reset(&svp->ssp1601);
}