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
struct TYPE_4__ {int /*<<< orphan*/ * displayName_; } ;
struct TYPE_5__ {TYPE_1__ org_apache_harmony_luni_platform_Endianness; } ;
struct TYPE_6__ {TYPE_2__ fields; } ;
typedef  TYPE_3__ org_apache_harmony_luni_platform_Endianness ;
typedef  int /*<<< orphan*/  java_lang_String ;
typedef  scalar_t__ JAVA_OBJECT ;

/* Variables and functions */
 scalar_t__ JAVA_NULL ; 
 int /*<<< orphan*/  __INIT_INSTANCE_MEMBERS_java_lang_Object (scalar_t__,int) ; 

void __INIT_INSTANCE_MEMBERS_org_apache_harmony_luni_platform_Endianness(JAVA_OBJECT me, int derivedClassWillRegisterFinalizer)
{
    __INIT_INSTANCE_MEMBERS_java_lang_Object(me, 0 || derivedClassWillRegisterFinalizer);
    ((org_apache_harmony_luni_platform_Endianness*) me)->fields.org_apache_harmony_luni_platform_Endianness.displayName_ = (java_lang_String*) JAVA_NULL;
    //XMLVM_BEGIN_WRAPPER[__INIT_INSTANCE_MEMBERS_org_apache_harmony_luni_platform_Endianness]
    //XMLVM_END_WRAPPER
}