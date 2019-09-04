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
typedef  int /*<<< orphan*/  U_8 ;
typedef  int I_32 ;

/* Variables and functions */
 int /*<<< orphan*/  SOCKET_CAST (int /*<<< orphan*/ ) ; 
 int errno ; 
 int /*<<< orphan*/  findError (int) ; 
 int hyerror_set_last_error (int,int /*<<< orphan*/ ) ; 
 int send (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 

I_32 hysock_write (hysocket_t sock, U_8 * buf, I_32 nbyte, I_32 flags)
{
    I_32 bytesSent = 0;
    
    bytesSent = send (SOCKET_CAST (sock), buf, nbyte, flags);
    
    if (-1 == bytesSent)
    {
        I_32 err = errno;
        return hyerror_set_last_error(err, findError(err));
    }
    else
    {
        return bytesSent;
    }
}