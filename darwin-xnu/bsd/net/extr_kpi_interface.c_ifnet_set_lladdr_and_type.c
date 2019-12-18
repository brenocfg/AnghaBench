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
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  ifnet_t ;
typedef  int /*<<< orphan*/  errno_t ;

/* Variables and functions */
 int /*<<< orphan*/  ifnet_set_lladdr_internal (int /*<<< orphan*/ ,void const*,size_t,int /*<<< orphan*/ ,int) ; 

errno_t
ifnet_set_lladdr_and_type(ifnet_t interface, const void* lladdr,
    size_t lladdr_len, u_char type)
{
	return (ifnet_set_lladdr_internal(interface, lladdr,
	    lladdr_len, type, 1));
}