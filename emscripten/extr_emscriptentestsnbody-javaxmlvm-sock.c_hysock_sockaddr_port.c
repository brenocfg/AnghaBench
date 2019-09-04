#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* hysockaddr_t ;
typedef  int /*<<< orphan*/  U_16 ;
struct TYPE_5__ {scalar_t__ sin_family; int /*<<< orphan*/  sin_port; } ;
struct TYPE_4__ {int /*<<< orphan*/  addr; } ;
typedef  TYPE_2__ OSSOCKADDR ;

/* Variables and functions */
 scalar_t__ OS_AF_INET4 ; 

U_16 hysock_sockaddr_port (hysockaddr_t handle)
{
    if (((OSSOCKADDR *) & handle->addr)->sin_family == OS_AF_INET4)
    {
        return ((OSSOCKADDR *) & handle->addr)->sin_port;
    }
#if defined(IPv6_FUNCTION_SUPPORT)
    else
    {
        return ((OSSOCKADDR_IN6 *) & handle->addr)->sin6_port;
    }
#endif
    
}