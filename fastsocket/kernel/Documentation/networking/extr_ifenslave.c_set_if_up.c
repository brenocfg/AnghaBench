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

/* Variables and functions */
 short IFF_UP ; 
 int set_if_flags (char*,short) ; 

__attribute__((used)) static int set_if_up(char *ifname, short flags)
{
	return set_if_flags(ifname, flags | IFF_UP);
}