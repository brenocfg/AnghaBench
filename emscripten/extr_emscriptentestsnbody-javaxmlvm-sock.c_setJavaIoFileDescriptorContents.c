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
struct TYPE_4__ {scalar_t__ descriptor_; } ;
struct TYPE_5__ {TYPE_1__ java_io_FileDescriptor; } ;
struct TYPE_6__ {TYPE_2__ fields; } ;
typedef  TYPE_3__ java_io_FileDescriptor ;
typedef  scalar_t__ JAVA_ULONG ;
typedef  scalar_t__ JAVA_OBJECT ;

/* Variables and functions */

void setJavaIoFileDescriptorContents (JAVA_OBJECT fd, void *value)
{
    ((java_io_FileDescriptor*) fd)->fields.java_io_FileDescriptor.descriptor_ = (JAVA_ULONG) value;    
}