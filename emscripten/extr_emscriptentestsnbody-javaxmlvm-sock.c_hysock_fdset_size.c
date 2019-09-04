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
typedef  int /*<<< orphan*/  hysocket_t ;
typedef  scalar_t__ I_32 ;

/* Variables and functions */
 scalar_t__ SOCKET_CAST (int /*<<< orphan*/ ) ; 

I_32 hysock_fdset_size (hysocket_t handle)
{
    return SOCKET_CAST (handle) + 1;
}