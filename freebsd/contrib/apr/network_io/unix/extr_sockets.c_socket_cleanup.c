#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  apr_status_t ;
struct TYPE_2__ {int socketdes; } ;
typedef  TYPE_1__ apr_socket_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_SUCCESS ; 
 scalar_t__ close (int) ; 
 int /*<<< orphan*/  errno ; 

__attribute__((used)) static apr_status_t socket_cleanup(void *sock)
{
    apr_socket_t *thesocket = sock;
    int sd = thesocket->socketdes;

    /* Set socket descriptor to -1 before close(), so that there is no
     * chance of returning an already closed FD from apr_os_sock_get().
     */
    thesocket->socketdes = -1;

    if (close(sd) == 0) {
        return APR_SUCCESS;
    }
    else {
        /* Restore, close() was not successful. */
        thesocket->socketdes = sd;

        return errno;
    }
}