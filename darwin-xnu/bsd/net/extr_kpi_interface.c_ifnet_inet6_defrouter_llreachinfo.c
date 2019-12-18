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
struct ifnet_llreach_info {int dummy; } ;
typedef  int /*<<< orphan*/  ifnet_t ;
typedef  int /*<<< orphan*/  errno_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 int /*<<< orphan*/  ifnet_defrouter_llreachinfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ifnet_llreach_info*) ; 

errno_t
ifnet_inet6_defrouter_llreachinfo(ifnet_t ifp, struct ifnet_llreach_info *iflri)
{
	return (ifnet_defrouter_llreachinfo(ifp, AF_INET6, iflri));
}