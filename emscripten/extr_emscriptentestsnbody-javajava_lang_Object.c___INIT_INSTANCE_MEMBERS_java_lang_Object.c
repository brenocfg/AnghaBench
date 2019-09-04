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
typedef  int /*<<< orphan*/  java_lang_Object_AddedMembers ;
struct TYPE_4__ {int /*<<< orphan*/ * addedMembers_; } ;
struct TYPE_5__ {TYPE_1__ java_lang_Object; } ;
struct TYPE_6__ {TYPE_2__ fields; } ;
typedef  TYPE_3__ java_lang_Object ;
typedef  scalar_t__ JAVA_OBJECT ;

/* Variables and functions */
 scalar_t__ JAVA_NULL ; 

void __INIT_INSTANCE_MEMBERS_java_lang_Object(JAVA_OBJECT me, int derivedClassWillRegisterFinalizer)
{
    ((java_lang_Object*) me)->fields.java_lang_Object.addedMembers_ = (java_lang_Object_AddedMembers*) JAVA_NULL;
    //XMLVM_BEGIN_WRAPPER[__INIT_INSTANCE_MEMBERS_java_lang_Object]
    //XMLVM_END_WRAPPER
}