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
typedef  int /*<<< orphan*/  org_xmlvm_runtime_XMLVMArray ;
struct TYPE_4__ {int /*<<< orphan*/ * ipaddress_; scalar_t__ family_; scalar_t__ addrCount_; scalar_t__ reached_; int /*<<< orphan*/ * waitReachable_; int /*<<< orphan*/ * hostName_; } ;
struct TYPE_5__ {TYPE_1__ java_net_InetAddress; } ;
struct TYPE_6__ {TYPE_2__ fields; } ;
typedef  TYPE_3__ java_net_InetAddress ;
typedef  int /*<<< orphan*/  java_lang_String ;
typedef  int /*<<< orphan*/  java_lang_Object ;
typedef  scalar_t__ JAVA_OBJECT ;

/* Variables and functions */
 scalar_t__ JAVA_NULL ; 
 int /*<<< orphan*/  __INIT_INSTANCE_MEMBERS_java_lang_Object (scalar_t__,int) ; 

void __INIT_INSTANCE_MEMBERS_java_net_InetAddress(JAVA_OBJECT me, int derivedClassWillRegisterFinalizer)
{
    __INIT_INSTANCE_MEMBERS_java_lang_Object(me, 0 || derivedClassWillRegisterFinalizer);
    ((java_net_InetAddress*) me)->fields.java_net_InetAddress.hostName_ = (java_lang_String*) JAVA_NULL;
    ((java_net_InetAddress*) me)->fields.java_net_InetAddress.waitReachable_ = (java_lang_Object*) JAVA_NULL;
    ((java_net_InetAddress*) me)->fields.java_net_InetAddress.reached_ = 0;
    ((java_net_InetAddress*) me)->fields.java_net_InetAddress.addrCount_ = 0;
    ((java_net_InetAddress*) me)->fields.java_net_InetAddress.family_ = 0;
    ((java_net_InetAddress*) me)->fields.java_net_InetAddress.ipaddress_ = (org_xmlvm_runtime_XMLVMArray*) JAVA_NULL;
    //XMLVM_BEGIN_WRAPPER[__INIT_INSTANCE_MEMBERS_java_net_InetAddress]
    //XMLVM_END_WRAPPER
}