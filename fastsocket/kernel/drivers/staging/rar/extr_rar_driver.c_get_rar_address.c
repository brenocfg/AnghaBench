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
struct RAR_address_struct {int low; int high; } ;

/* Variables and functions */
 int ENODEV ; 
 struct RAR_address_struct* rar_addr ; 
 scalar_t__ registered ; 

int get_rar_address(int rar_index,struct RAR_address_struct *addresses)
{
	if (registered && (rar_index < 3) && (rar_index >= 0)) {
		*addresses=rar_addr[rar_index];
		/* strip off lock bit information  */
		addresses->low = addresses->low & 0xfffffff0;
		addresses->high = addresses->high & 0xfffffff0;
		return 0;
		}

	else {
		return -ENODEV;
		}
}