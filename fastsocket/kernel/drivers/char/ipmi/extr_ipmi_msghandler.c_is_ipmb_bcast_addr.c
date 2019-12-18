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
struct ipmi_addr {scalar_t__ addr_type; } ;

/* Variables and functions */
 scalar_t__ IPMI_IPMB_BROADCAST_ADDR_TYPE ; 

__attribute__((used)) static int is_ipmb_bcast_addr(struct ipmi_addr *addr)
{
	return addr->addr_type == IPMI_IPMB_BROADCAST_ADDR_TYPE;
}