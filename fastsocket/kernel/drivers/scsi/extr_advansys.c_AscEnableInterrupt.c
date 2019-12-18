#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int ushort ;
typedef  int /*<<< orphan*/  PortAddr ;

/* Variables and functions */
 int ASC_CFG0_HOST_INT_ON ; 
 int AscGetChipCfgLsw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AscSetChipCfgLsw (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void AscEnableInterrupt(PortAddr iop_base)
{
	ushort cfg;

	cfg = AscGetChipCfgLsw(iop_base);
	AscSetChipCfgLsw(iop_base, cfg | ASC_CFG0_HOST_INT_ON);
}