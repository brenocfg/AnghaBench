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
struct pollfd {int events; scalar_t__ revents; int /*<<< orphan*/  fd; } ;
typedef  TYPE_1__* hysocket_t ;
struct TYPE_3__ {int /*<<< orphan*/  sock; } ;
typedef  scalar_t__ I_32 ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 int HYPORT_ERROR_SOCKET_OPFAILED ; 
 int HYPORT_ERROR_SOCKET_TIMEOUT ; 
 int POLLIN ; 
 int POLLPRI ; 
 int TO_MILLIS (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ errno ; 
 scalar_t__ poll (struct pollfd*,int,scalar_t__) ; 

int selectRead(hysocket_t hysocketP, I_32 uSecTime, BOOLEAN accept)
{
    I_32 result = 0;
    I_32 timeout;
    struct pollfd my_pollfd;
    
    timeout = uSecTime >= 0 ? TO_MILLIS(0, uSecTime) : -1;
    my_pollfd.fd = hysocketP->sock;
    my_pollfd.events = POLLIN | POLLPRI;
    my_pollfd.revents = 0;
    do {
        result = poll (&my_pollfd, 1, timeout);
    } while (result == -1 && errno == EINTR);
    
    if (result == 0)
        return HYPORT_ERROR_SOCKET_TIMEOUT;
    
    if (result == -1)
        return HYPORT_ERROR_SOCKET_OPFAILED;
    
    return result;
}