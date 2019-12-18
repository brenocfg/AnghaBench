#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned int nl_nonroot; } ;

/* Variables and functions */
 unsigned int MAX_LINKS ; 
 TYPE_1__* nl_table ; 

void netlink_set_nonroot(int protocol, unsigned int flags)
{
	if ((unsigned int)protocol < MAX_LINKS)
		nl_table[protocol].nl_nonroot = flags;
}