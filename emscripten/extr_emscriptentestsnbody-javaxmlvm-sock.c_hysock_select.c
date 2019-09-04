#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* hytimeval_t ;
typedef  TYPE_2__* hyfdset_t ;
struct TYPE_8__ {int /*<<< orphan*/  handle; } ;
struct TYPE_7__ {int /*<<< orphan*/  time; } ;
typedef  scalar_t__ I_32 ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 scalar_t__ FD_SETSIZE ; 
 int /*<<< orphan*/  HYPORT_ERROR_SOCKET_INTERRUPTED ; 
 int /*<<< orphan*/  HYPORT_ERROR_SOCKET_OPFAILED ; 
 scalar_t__ HYPORT_ERROR_SOCKET_TIMEOUT ; 
 int /*<<< orphan*/  HYPORT_ERROR_SOCKET_UNIX_EINVAL ; 
 int /*<<< orphan*/  HYSOCKDEBUG (char*,scalar_t__) ; 
 scalar_t__ errno ; 
 scalar_t__ hyerror_set_last_error (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ select (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

I_32 hysock_select (I_32 nfds, hyfdset_t readfds, hyfdset_t writefds, hyfdset_t exceptfds, hytimeval_t timeout)
{
    I_32 rc = 0;
    I_32 result = 0;
    
    if (nfds >= FD_SETSIZE) {
        rc = hyerror_set_last_error(rc, HYPORT_ERROR_SOCKET_UNIX_EINVAL);
        return -1;
    }
    result = select (nfds, 
                     readfds == NULL ? NULL : &readfds->handle,
                     writefds == NULL ? NULL : &writefds->handle,
                     exceptfds == NULL ? NULL : &exceptfds->handle,
                     timeout == NULL ? NULL : &timeout->time);
    
    if (result == -1) {
        HYSOCKDEBUG ("<select failed, err=%d>\n", errno);
        
        if (errno == EINTR) {
            rc = hyerror_set_last_error(rc, HYPORT_ERROR_SOCKET_INTERRUPTED);
            
        }
        else {
            rc = hyerror_set_last_error(rc, HYPORT_ERROR_SOCKET_OPFAILED);
        }
    }
    else {
        if (result) {
            rc = result;
        } 
        else {
            rc = HYPORT_ERROR_SOCKET_TIMEOUT;
        }
    }
    return rc;
}