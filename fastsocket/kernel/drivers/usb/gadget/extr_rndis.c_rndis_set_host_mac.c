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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int /*<<< orphan*/  const* host_mac; } ;

/* Variables and functions */
 TYPE_1__* rndis_per_dev_params ; 

void rndis_set_host_mac (int configNr, const u8 *addr)
{
	rndis_per_dev_params [configNr].host_mac = addr;
}