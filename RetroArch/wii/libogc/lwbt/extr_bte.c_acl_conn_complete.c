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
struct bd_addr {int dummy; } ;
typedef  int /*<<< orphan*/  err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_OK ; 
 int /*<<< orphan*/  hci_write_link_policy_settings (struct bd_addr*,int) ; 

err_t acl_conn_complete(void *arg,struct bd_addr *bdaddr)
{
	//printf("acl_conn_complete\n");
	//memcpy(&(btstate.acl_bdaddr),bdaddr,6);

	hci_write_link_policy_settings(bdaddr,0x0005);
	return ERR_OK;
}