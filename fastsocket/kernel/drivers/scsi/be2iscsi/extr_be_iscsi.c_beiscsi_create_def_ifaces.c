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
struct beiscsi_hba {int dummy; } ;
struct be_cmd_get_if_info_resp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BE2_IPV4 ; 
 int /*<<< orphan*/  BE2_IPV6 ; 
 int /*<<< orphan*/  beiscsi_create_ipv4_iface (struct beiscsi_hba*) ; 
 int /*<<< orphan*/  beiscsi_create_ipv6_iface (struct beiscsi_hba*) ; 
 int /*<<< orphan*/  mgmt_get_if_info (struct beiscsi_hba*,int /*<<< orphan*/ ,struct be_cmd_get_if_info_resp*) ; 

void beiscsi_create_def_ifaces(struct beiscsi_hba *phba)
{
	struct be_cmd_get_if_info_resp if_info;

	if (!mgmt_get_if_info(phba, BE2_IPV4, &if_info))
		beiscsi_create_ipv4_iface(phba);

	if (!mgmt_get_if_info(phba, BE2_IPV6, &if_info))
		beiscsi_create_ipv6_iface(phba);
}