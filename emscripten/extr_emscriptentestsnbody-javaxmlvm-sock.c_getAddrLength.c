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
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  hysockaddr_t ;
typedef  int /*<<< orphan*/  OSSOCKADDR ;

/* Variables and functions */

__attribute__((used)) static socklen_t getAddrLength(hysockaddr_t addr)
{
    return
#if defined(IPv6_FUNCTION_SUPPORT)
    ((OSSOCKADDR *) & addr->addr)->sin_family == OS_AF_INET6 ?
    sizeof(OSSOCKADDR_IN6) :
#endif
    sizeof(OSSOCKADDR);
}