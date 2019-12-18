#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_5__ {TYPE_1__* adapt; scalar_t__ io_addr; } ;
typedef  TYPE_2__ ips_ha_t ;
struct TYPE_4__ {scalar_t__ hw_status_tail; scalar_t__ hw_status_start; scalar_t__ status; scalar_t__ p_status_tail; scalar_t__ p_status_end; scalar_t__ p_status_start; } ;

/* Variables and functions */
 scalar_t__ IPS_MAX_CMDS ; 
 scalar_t__ IPS_REG_SQER ; 
 scalar_t__ IPS_REG_SQHR ; 
 scalar_t__ IPS_REG_SQSR ; 
 scalar_t__ IPS_REG_SQTR ; 
 scalar_t__ IPS_STATUS_Q_SIZE ; 
 scalar_t__ IPS_STATUS_SIZE ; 
 int /*<<< orphan*/  METHOD_TRACE (char*,int) ; 
 int /*<<< orphan*/  outl (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void
ips_statinit(ips_ha_t * ha)
{
	uint32_t phys_status_start;

	METHOD_TRACE("ips_statinit", 1);

	ha->adapt->p_status_start = ha->adapt->status;
	ha->adapt->p_status_end = ha->adapt->status + IPS_MAX_CMDS;
	ha->adapt->p_status_tail = ha->adapt->status;

	phys_status_start = ha->adapt->hw_status_start;
	outl(phys_status_start, ha->io_addr + IPS_REG_SQSR);
	outl(phys_status_start + IPS_STATUS_Q_SIZE,
	     ha->io_addr + IPS_REG_SQER);
	outl(phys_status_start + IPS_STATUS_SIZE,
	     ha->io_addr + IPS_REG_SQHR);
	outl(phys_status_start, ha->io_addr + IPS_REG_SQTR);

	ha->adapt->hw_status_tail = phys_status_start;
}