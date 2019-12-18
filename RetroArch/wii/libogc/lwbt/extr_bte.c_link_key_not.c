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
typedef  int /*<<< orphan*/  u8_t ;
struct bd_addr {int dummy; } ;
typedef  int /*<<< orphan*/  err_t ;

/* Variables and functions */
 int /*<<< orphan*/  hci_write_stored_link_key (struct bd_addr*,int /*<<< orphan*/ *) ; 

err_t link_key_not(void *arg,struct bd_addr *bdaddr,u8_t *key)
{
	//printf("link_key_not\n");
	return hci_write_stored_link_key(bdaddr,key);
}