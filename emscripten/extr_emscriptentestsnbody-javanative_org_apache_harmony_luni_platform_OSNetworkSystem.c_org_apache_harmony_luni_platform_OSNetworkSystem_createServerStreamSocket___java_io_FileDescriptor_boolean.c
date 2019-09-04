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
typedef  int /*<<< orphan*/  JAVA_OBJECT ;
typedef  int /*<<< orphan*/  JAVA_BOOLEAN ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  HYSOCK_STREAM ; 
 int /*<<< orphan*/  HY_SOL_SOCKET ; 
 int /*<<< orphan*/  HY_SO_REUSEADDR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  createSocket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ getJavaIoFileDescriptorContentsAsAPointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hysock_setopt_bool (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void org_apache_harmony_luni_platform_OSNetworkSystem_createServerStreamSocket___java_io_FileDescriptor_boolean(JAVA_OBJECT me, JAVA_OBJECT n1, JAVA_BOOLEAN n2)
{
    //XMLVM_BEGIN_NATIVE[org_apache_harmony_luni_platform_OSNetworkSystem_createServerStreamSocket___java_io_FileDescriptor_boolean]
    hysocket_t socketP;
    BOOLEAN value = TRUE;
    
    createSocket(n1, HYSOCK_STREAM, n2);
    
    /* Also sets HY_SO_REUSEADDR = TRUE on Linux only */
    socketP = (hysocket_t) getJavaIoFileDescriptorContentsAsAPointer(n1);
    hysock_setopt_bool (socketP, HY_SOL_SOCKET, HY_SO_REUSEADDR, &value);
    //XMLVM_END_NATIVE
}