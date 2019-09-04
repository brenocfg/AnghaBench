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
struct TYPE_4__ {scalar_t__ scope_id_; } ;
struct TYPE_5__ {TYPE_1__ java_net_Inet6Address; } ;
struct TYPE_6__ {TYPE_2__ fields; } ;
typedef  TYPE_3__ java_net_Inet6Address ;
typedef  scalar_t__ U_32 ;
typedef  scalar_t__ JAVA_OBJECT ;

/* Variables and functions */
 scalar_t__ XMLVM_ISA (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __CLASS_java_net_Inet6Address ; 

void netGetJavaNetInetAddressScopeId (JAVA_OBJECT anInetAddress, U_32* scope_id)
{
    if (XMLVM_ISA(anInetAddress, __CLASS_java_net_Inet6Address)) {
        java_net_Inet6Address* addr = (java_net_Inet6Address*) anInetAddress;
        *scope_id = addr->fields.java_net_Inet6Address.scope_id_;
    }
    else {
        *scope_id = 0;
    }
}