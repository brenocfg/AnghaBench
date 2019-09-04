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
struct sockaddr {int dummy; } ;
struct ifaddr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFSCOPE_NONE ; 
 struct ifaddr* ifa_ifwithnet_common (struct sockaddr const*,int /*<<< orphan*/ ) ; 

struct ifaddr *
ifa_ifwithnet(const struct sockaddr *addr)
{
	return (ifa_ifwithnet_common(addr, IFSCOPE_NONE));
}