#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  array_; int /*<<< orphan*/  length_; } ;
struct TYPE_10__ {TYPE_3__ org_xmlvm_runtime_XMLVMArray; } ;
struct TYPE_11__ {TYPE_4__ fields; } ;
typedef  TYPE_5__ org_xmlvm_runtime_XMLVMArray ;
struct TYPE_7__ {TYPE_5__* ipaddress_; } ;
struct TYPE_8__ {TYPE_1__ java_net_InetAddress; } ;
struct TYPE_12__ {TYPE_2__ fields; } ;
typedef  TYPE_6__ java_net_InetAddress ;
typedef  int /*<<< orphan*/  U_8 ;
typedef  int /*<<< orphan*/  U_32 ;
typedef  scalar_t__ JAVA_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  XMLVM_MEMCPY (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void netGetJavaNetInetAddressValue (JAVA_OBJECT anInetAddress, U_8* buffer, U_32* length)
{
    org_xmlvm_runtime_XMLVMArray* byte_array = ((java_net_InetAddress*) anInetAddress)->fields.java_net_InetAddress.ipaddress_;
    *length = byte_array->fields.org_xmlvm_runtime_XMLVMArray.length_;
    XMLVM_MEMCPY(buffer, byte_array->fields.org_xmlvm_runtime_XMLVMArray.array_, *length);
}