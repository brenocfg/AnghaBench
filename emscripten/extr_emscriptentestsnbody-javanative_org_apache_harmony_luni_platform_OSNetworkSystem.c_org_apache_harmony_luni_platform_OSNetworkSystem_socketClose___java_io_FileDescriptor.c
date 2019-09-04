#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int descriptor_; } ;
struct TYPE_9__ {TYPE_1__ java_io_FileDescriptor; } ;
struct TYPE_10__ {TYPE_2__ fields; } ;
typedef  TYPE_3__ java_io_FileDescriptor ;
typedef  int /*<<< orphan*/  hysocket_t ;
typedef  TYPE_3__* JAVA_OBJECT ;
typedef  int /*<<< orphan*/  I_32 ;

/* Variables and functions */
 int /*<<< orphan*/  getJavaIoFileDescriptorContentsAsAPointer (TYPE_3__*) ; 
 int /*<<< orphan*/  hysock_close (int /*<<< orphan*/ *) ; 
 scalar_t__ hysock_socketIsValid (int /*<<< orphan*/ ) ; 

void org_apache_harmony_luni_platform_OSNetworkSystem_socketClose___java_io_FileDescriptor(JAVA_OBJECT me, JAVA_OBJECT n1)
{
    //XMLVM_BEGIN_NATIVE[org_apache_harmony_luni_platform_OSNetworkSystem_socketClose___java_io_FileDescriptor]
    hysocket_t socketP;
    I_32 result = 0;
    
    java_io_FileDescriptor* fileDescriptor = n1;
    
    socketP = getJavaIoFileDescriptorContentsAsAPointer(fileDescriptor);
    if (hysock_socketIsValid(socketP)) {
        /* Set the file descriptor before closing so the select polling loop will terminate. */
        /* Some platforms wait in the socket close. */
        fileDescriptor->fields.java_io_FileDescriptor.descriptor_ = -1;
        result = hysock_close(&socketP);
    }
    //XMLVM_END_NATIVE
}