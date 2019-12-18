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
typedef  enum port_event { ____Placeholder_port_event } port_event ;

/* Variables and functions */
 int /*<<< orphan*/  SAS_DPRINTK (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * sas_porte_str ; 

void sas_dprint_porte(int phyid, enum port_event pe)
{
	SAS_DPRINTK("phy%d: port event: %s\n", phyid, sas_porte_str[pe]);
}