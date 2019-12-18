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
struct beiscsi_hba {scalar_t__ ipv4_iface; scalar_t__ ipv6_iface; } ;

/* Variables and functions */
 int /*<<< orphan*/  iscsi_destroy_iface (scalar_t__) ; 

void beiscsi_destroy_def_ifaces(struct beiscsi_hba *phba)
{
	if (phba->ipv6_iface)
		iscsi_destroy_iface(phba->ipv6_iface);
	if (phba->ipv4_iface)
		iscsi_destroy_iface(phba->ipv4_iface);
}