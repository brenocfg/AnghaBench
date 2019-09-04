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
typedef  int /*<<< orphan*/  java_io_FileDescriptor ;
typedef  int /*<<< orphan*/  hysockaddr_struct ;
typedef  int /*<<< orphan*/  U_16 ;
typedef  int /*<<< orphan*/ * JAVA_OBJECT ;
typedef  int /*<<< orphan*/  JAVA_INT ;
typedef  int /*<<< orphan*/  JAVA_BOOLEAN ;
typedef  scalar_t__ I_32 ;

/* Variables and functions */
 int /*<<< orphan*/  hysock_ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hysock_sockaddr_port (int /*<<< orphan*/ *) ; 
 scalar_t__ netGetSockAddr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

JAVA_INT org_apache_harmony_luni_platform_OSNetworkSystem_getSocketLocalPort___java_io_FileDescriptor_boolean(JAVA_OBJECT me, JAVA_OBJECT n1, JAVA_BOOLEAN n2)
{
    //XMLVM_BEGIN_NATIVE[org_apache_harmony_luni_platform_OSNetworkSystem_getSocketLocalPort___java_io_FileDescriptor_boolean]
    I_32 result;
    hysockaddr_struct sockaddrP;
    U_16 nPort, hPort;
    java_io_FileDescriptor* fileDescriptor = n1;
    JAVA_BOOLEAN preferIPv6Addresses = n2;
    
    result = netGetSockAddr(fileDescriptor, &sockaddrP, preferIPv6Addresses);
    if (0 != result) {
        /* The java spec does not indicate any exceptions on this call */
        return (JAVA_INT) 0;
    }
    
    nPort = hysock_sockaddr_port(&sockaddrP);
    hPort = hysock_ntohs(nPort);
    return (JAVA_INT) hPort;
    //XMLVM_END_NATIVE
}