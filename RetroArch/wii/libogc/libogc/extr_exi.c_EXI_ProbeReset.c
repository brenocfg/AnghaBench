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
struct TYPE_2__ {scalar_t__ exi_idtime; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXI_CHANNEL_0 ; 
 int /*<<< orphan*/  EXI_DEVICE_2 ; 
 int /*<<< orphan*/  EXI_GetID (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __exi_probe (int) ; 
 int /*<<< orphan*/  exi_id_serport1 ; 
 TYPE_1__* eximap ; 
 scalar_t__* last_exi_idtime ; 

void EXI_ProbeReset()
{
	last_exi_idtime[0] = 0;
	last_exi_idtime[1] = 0;

	eximap[0].exi_idtime = 0;
	eximap[1].exi_idtime = 0;

	__exi_probe(0);
	__exi_probe(1);
	EXI_GetID(EXI_CHANNEL_0,EXI_DEVICE_2,&exi_id_serport1);
}