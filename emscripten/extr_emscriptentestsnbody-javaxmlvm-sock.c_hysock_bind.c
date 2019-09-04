#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  hysocket_t ;
typedef  TYPE_1__* hysockaddr_t ;
struct TYPE_4__ {int /*<<< orphan*/  addr; } ;
typedef  int /*<<< orphan*/  I_32 ;

/* Variables and functions */
 int /*<<< orphan*/  HYPORT_ERROR_SOCKET_ADDRNOTAVAIL ; 
 int /*<<< orphan*/  SOCKET_CAST (int /*<<< orphan*/ ) ; 
 scalar_t__ bind (int /*<<< orphan*/ ,struct sockaddr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  getAddrLength (TYPE_1__*) ; 
 int /*<<< orphan*/  hyerror_set_last_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

I_32 hysock_bind (hysocket_t sock, hysockaddr_t addr)
{
    I_32 rc = 0;
    I_32 length = getAddrLength(addr);
    
    if (bind
        (SOCKET_CAST (sock), (struct sockaddr *) &addr->addr, length) < 0)
    {
        rc = errno;
        rc = hyerror_set_last_error(rc, HYPORT_ERROR_SOCKET_ADDRNOTAVAIL);
    }
    return rc;
}