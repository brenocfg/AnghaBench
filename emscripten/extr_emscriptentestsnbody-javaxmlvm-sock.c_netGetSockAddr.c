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
typedef  int /*<<< orphan*/  hysockaddr_t ;
typedef  int /*<<< orphan*/  U_8 ;
typedef  int /*<<< orphan*/  JAVA_OBJECT ;
typedef  scalar_t__ JAVA_BOOLEAN ;
typedef  int /*<<< orphan*/  I_32 ;

/* Variables and functions */
 int /*<<< orphan*/  HYADDR_FAMILY_AFINET4 ; 
 int /*<<< orphan*/  HYADDR_FAMILY_UNSPEC ; 
 int /*<<< orphan*/  HYPORT_ERROR_SOCKET_UNKNOWNSOCKET ; 
 int HYSOCK_INADDR6_LEN ; 
 int HYSOCK_INADDR_LEN ; 
 int /*<<< orphan*/  getJavaIoFileDescriptorContentsAsAPointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hysock_getsockname (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hysock_sockaddr_init6 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hysock_socketIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

I_32 netGetSockAddr (JAVA_OBJECT fileDescriptor, hysockaddr_t sockaddrP, JAVA_BOOLEAN preferIPv6Addresses)
{
    I_32 result = 0;
    hysocket_t socketP;
    U_8 ipAddr[HYSOCK_INADDR6_LEN];
    memset (ipAddr, 0, HYSOCK_INADDR6_LEN);
    
    socketP = getJavaIoFileDescriptorContentsAsAPointer (fileDescriptor);
    if (!hysock_socketIsValid (socketP))
    {
        return HYPORT_ERROR_SOCKET_UNKNOWNSOCKET;
    }
    else
    {
        if (preferIPv6Addresses)
        {
            hysock_sockaddr_init6 (sockaddrP, ipAddr, HYSOCK_INADDR6_LEN,
                                   HYADDR_FAMILY_UNSPEC, 0, 0, 0, socketP);
            result = hysock_getsockname (socketP, sockaddrP);
        }
        else
        {
            hysock_sockaddr_init6 (sockaddrP, ipAddr, HYSOCK_INADDR_LEN,
                                   HYADDR_FAMILY_AFINET4, 0, 0, 0, socketP);
            result = hysock_getsockname (socketP, sockaddrP);
        }
        return result;
    }
}