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
struct iowa_bus {TYPE_1__* phb; } ;
struct TYPE_2__ {int /*<<< orphan*/  cfg_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  PEXDMRDEN0 ; 
 int /*<<< orphan*/  PEX_IN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void scc_pciex_io_flush(struct iowa_bus *bus)
{
	(void)PEX_IN(bus->phb->cfg_addr, PEXDMRDEN0);
}