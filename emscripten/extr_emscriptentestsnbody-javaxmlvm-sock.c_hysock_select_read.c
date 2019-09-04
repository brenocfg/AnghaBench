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
struct pollfd {int events; scalar_t__ revents; int /*<<< orphan*/  fd; } ;
typedef  int /*<<< orphan*/  hysocket_t ;
typedef  int I_32 ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  HYPORT_ERROR_SOCKET_INTERRUPTED ; 
 int /*<<< orphan*/  HYPORT_ERROR_SOCKET_OPFAILED ; 
 int HYPORT_ERROR_SOCKET_TIMEOUT ; 
 int /*<<< orphan*/  HYSOCKDEBUG (char*,scalar_t__) ; 
 int POLLIN ; 
 int POLLPRI ; 
 int /*<<< orphan*/  SOCKET_CAST (int /*<<< orphan*/ ) ; 
 int TO_MILLIS (int,int) ; 
 scalar_t__ errno ; 
 int hyerror_set_last_error (int,int /*<<< orphan*/ ) ; 
 int poll (struct pollfd*,int,int) ; 

I_32 hysock_select_read (hysocket_t hysocketP, I_32 secTime, I_32 uSecTime, BOOLEAN accept)
{
    // Current implementation uses poll() system routine since select()
    // has issues if fd_num is greater than FD_SETSIZE. See HARMONY-4077.
    
    int poll_timeout;
    I_32 result = 0;
    I_32 rc = 0;
    struct pollfd my_pollfd;
    
    my_pollfd.fd = SOCKET_CAST(hysocketP);
    my_pollfd.events = POLLIN | POLLPRI;
    my_pollfd.revents = 0;
    poll_timeout = TO_MILLIS(secTime, uSecTime);
    
    result = poll(&my_pollfd, 1, poll_timeout);
    
    if (result == -1) {
        HYSOCKDEBUG ("<poll failed, err=%d>\n", errno);
        
        if (errno == EINTR) {
            rc = hyerror_set_last_error(rc, HYPORT_ERROR_SOCKET_INTERRUPTED);
        } else {
            rc = hyerror_set_last_error(rc, HYPORT_ERROR_SOCKET_OPFAILED);
        }
    } else {
        if (result || poll_timeout == 0) {
            rc = result;
        } else {
            rc = HYPORT_ERROR_SOCKET_TIMEOUT;
        }
    }
    
    return rc;
}