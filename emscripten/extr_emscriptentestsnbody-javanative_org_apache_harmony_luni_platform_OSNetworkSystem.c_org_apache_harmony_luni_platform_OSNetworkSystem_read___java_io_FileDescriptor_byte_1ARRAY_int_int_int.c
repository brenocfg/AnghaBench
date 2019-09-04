#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * array_; } ;
struct TYPE_5__ {TYPE_1__ org_xmlvm_runtime_XMLVMArray; } ;
struct TYPE_6__ {TYPE_2__ fields; } ;
typedef  TYPE_3__ org_xmlvm_runtime_XMLVMArray ;
typedef  int /*<<< orphan*/  java_io_FileDescriptor ;
typedef  void* JAVA_OBJECT ;
typedef  int /*<<< orphan*/  JAVA_LONG ;
typedef  int JAVA_INT ;
typedef  int /*<<< orphan*/  JAVA_ARRAY_BYTE ;

/* Variables and functions */
 int org_apache_harmony_luni_platform_OSNetworkSystem_readDirect___java_io_FileDescriptor_long_int_int (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 

JAVA_INT org_apache_harmony_luni_platform_OSNetworkSystem_read___java_io_FileDescriptor_byte_1ARRAY_int_int_int(JAVA_OBJECT me, JAVA_OBJECT n1, JAVA_OBJECT n2, JAVA_INT n3, JAVA_INT n4, JAVA_INT n5)
{
    //XMLVM_BEGIN_NATIVE[org_apache_harmony_luni_platform_OSNetworkSystem_read___java_io_FileDescriptor_byte_1ARRAY_int_int_int]
    JAVA_ARRAY_BYTE* message;
    JAVA_INT result;
    
    java_io_FileDescriptor* fd = n1;
    org_xmlvm_runtime_XMLVMArray* data = n2;
    JAVA_INT offset = n3;
    JAVA_INT count = n4;
    JAVA_INT timeout = n5;
    
    /* Get a pointer to the start of the bytearray */
    message = data->fields.org_xmlvm_runtime_XMLVMArray.array_;
    
    /* Read directly into the byte array */
    result =
    org_apache_harmony_luni_platform_OSNetworkSystem_readDirect___java_io_FileDescriptor_long_int_int
            (me, fd, (JAVA_LONG) (message + offset), count, timeout);
    
    return result;
    //XMLVM_END_NATIVE
}