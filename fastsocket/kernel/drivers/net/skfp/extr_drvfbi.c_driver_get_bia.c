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
struct TYPE_3__ {int /*<<< orphan*/ * a; } ;
struct TYPE_4__ {TYPE_1__ fddi_phys_addr; } ;
struct s_smc {TYPE_2__ hw; } ;
struct fddi_addr {int /*<<< orphan*/ * a; } ;

/* Variables and functions */
 int /*<<< orphan*/  bitrev8 (int /*<<< orphan*/ ) ; 

void driver_get_bia(struct s_smc *smc, struct fddi_addr *bia_addr)
{
	int i ;

	for (i = 0 ; i < 6 ; i++)
		bia_addr->a[i] = bitrev8(smc->hw.fddi_phys_addr.a[i]);
}