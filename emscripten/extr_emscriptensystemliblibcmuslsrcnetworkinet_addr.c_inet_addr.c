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
struct in_addr {int s_addr; } ;
typedef  int in_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  __inet_aton (char const*,struct in_addr*) ; 

in_addr_t inet_addr(const char *p)
{
	struct in_addr a;
	if (!__inet_aton(p, &a)) return -1;
	return a.s_addr;
}