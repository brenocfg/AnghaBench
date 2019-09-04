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
typedef  scalar_t__ hysocket_t ;
typedef  int /*<<< orphan*/  I_32 ;

/* Variables and functions */
 int /*<<< orphan*/  HYPORT_ERROR_SOCKET_BADSOCKET ; 
 int /*<<< orphan*/  HYPORT_ERROR_SOCKET_UNIX_EBADF ; 
 scalar_t__ INVALID_SOCKET ; 
 int /*<<< orphan*/  SOCKET_CAST (scalar_t__) ; 
 scalar_t__ close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  hyerror_set_last_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

I_32 hysock_close (hysocket_t * sock)
{
    I_32 rc = 0;
    
    if (*sock == INVALID_SOCKET) {
        return hyerror_set_last_error(HYPORT_ERROR_SOCKET_UNIX_EBADF, HYPORT_ERROR_SOCKET_BADSOCKET);
    }
    
    if (close (SOCKET_CAST (*sock)) < 0) {
        rc = errno;
        rc = hyerror_set_last_error(rc, HYPORT_ERROR_SOCKET_BADSOCKET);
    }
    
    *sock = INVALID_SOCKET;
    return rc;
}