#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sockaddr {int dummy; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  hysocket_t ;
typedef  TYPE_1__* hysockaddr_t ;
struct TYPE_3__ {int /*<<< orphan*/  addr; } ;
typedef  int /*<<< orphan*/  I_32 ;

/* Variables and functions */
 int /*<<< orphan*/  SOCKET_CAST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  findError (int /*<<< orphan*/ ) ; 
 scalar_t__ getsockname (int /*<<< orphan*/ ,struct sockaddr*,int*) ; 
 int /*<<< orphan*/  hyerror_set_last_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

I_32 hysock_getsockname (hysocket_t handle, hysockaddr_t addrHandle)
{
    socklen_t addrlen = sizeof (addrHandle->addr);
#ifndef XMLVM_ASM_JS    
    if (getsockname
        (SOCKET_CAST (handle), (struct sockaddr *) &addrHandle->addr,
         &addrlen) != 0)
    {
        I_32 err = errno;
        return hyerror_set_last_error(err, findError(err));
    }
#endif
    return 0;
}