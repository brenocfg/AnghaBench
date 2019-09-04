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
typedef  int /*<<< orphan*/  I_32 ;

/* Variables and functions */
 int /*<<< orphan*/  HYPORT_ERROR_SOCKET_OPFAILED ; 
 int /*<<< orphan*/  HYSOCKDEBUG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SOCKET_CAST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  hyerror_set_last_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ listen (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

I_32 hysock_listen (hysocket_t sock, I_32 backlog)
{
    I_32 rc = 0;
    
    if (listen (SOCKET_CAST (sock), backlog) < 0)
    {
        rc = errno;
        HYSOCKDEBUG ("<listen failed, err=%d>\n", rc);
        rc = hyerror_set_last_error(rc, HYPORT_ERROR_SOCKET_OPFAILED);
    }
    return rc;
}