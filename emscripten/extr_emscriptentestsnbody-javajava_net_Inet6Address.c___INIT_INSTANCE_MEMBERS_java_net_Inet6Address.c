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
struct TYPE_4__ {int /*<<< orphan*/ * scopedIf_; int /*<<< orphan*/ * ifname_; scalar_t__ scope_ifname_set_; scalar_t__ scope_id_set_; scalar_t__ scope_id_; } ;
struct TYPE_5__ {TYPE_1__ java_net_Inet6Address; } ;
struct TYPE_6__ {TYPE_2__ fields; } ;
typedef  TYPE_3__ java_net_Inet6Address ;
typedef  int /*<<< orphan*/  java_lang_String ;
typedef  int /*<<< orphan*/  java_lang_Object ;
typedef  scalar_t__ JAVA_OBJECT ;

/* Variables and functions */
 scalar_t__ JAVA_NULL ; 
 int /*<<< orphan*/  __INIT_INSTANCE_MEMBERS_java_net_InetAddress (scalar_t__,int) ; 

void __INIT_INSTANCE_MEMBERS_java_net_Inet6Address(JAVA_OBJECT me, int derivedClassWillRegisterFinalizer)
{
    __INIT_INSTANCE_MEMBERS_java_net_InetAddress(me, 0 || derivedClassWillRegisterFinalizer);
    ((java_net_Inet6Address*) me)->fields.java_net_Inet6Address.scope_id_ = 0;
    ((java_net_Inet6Address*) me)->fields.java_net_Inet6Address.scope_id_set_ = 0;
    ((java_net_Inet6Address*) me)->fields.java_net_Inet6Address.scope_ifname_set_ = 0;
    ((java_net_Inet6Address*) me)->fields.java_net_Inet6Address.ifname_ = (java_lang_String*) JAVA_NULL;
    ((java_net_Inet6Address*) me)->fields.java_net_Inet6Address.scopedIf_ = (java_lang_Object*) JAVA_NULL;
    //XMLVM_BEGIN_WRAPPER[__INIT_INSTANCE_MEMBERS_java_net_Inet6Address]
    //XMLVM_END_WRAPPER
}