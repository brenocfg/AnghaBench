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
struct uwb_rc {int dummy; } ;
struct uwb_dev_addr {int* data; } ;

/* Variables and functions */
 scalar_t__ __uwb_dev_addr_assigned (struct uwb_rc*,struct uwb_dev_addr*) ; 
 int /*<<< orphan*/  get_random_bytes (int*,int) ; 
 int uwb_rc_dev_addr_set (struct uwb_rc*,struct uwb_dev_addr*) ; 

int uwb_rc_dev_addr_assign(struct uwb_rc *rc)
{
	struct uwb_dev_addr new_addr;

	do {
		get_random_bytes(new_addr.data, sizeof(new_addr.data));
	} while (new_addr.data[0] == 0x00 || new_addr.data[0] == 0xff
		 || __uwb_dev_addr_assigned(rc, &new_addr));

	return uwb_rc_dev_addr_set(rc, &new_addr);
}