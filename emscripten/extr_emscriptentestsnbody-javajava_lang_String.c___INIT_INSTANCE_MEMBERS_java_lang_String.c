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
typedef  int /*<<< orphan*/  org_apache_harmony_niochar_charset_UTF_8 ;
struct TYPE_4__ {scalar_t__ hashCode_; scalar_t__ count_; scalar_t__ offset_; int /*<<< orphan*/ * value_; int /*<<< orphan*/ * charset3_; int /*<<< orphan*/ * charset2_; int /*<<< orphan*/ * charset_; } ;
struct TYPE_5__ {TYPE_1__ java_lang_String; } ;
struct TYPE_6__ {TYPE_2__ fields; } ;
typedef  TYPE_3__ java_lang_String ;
typedef  int /*<<< orphan*/  java_lang_Object ;
typedef  scalar_t__ JAVA_OBJECT ;

/* Variables and functions */
 scalar_t__ JAVA_NULL ; 
 int /*<<< orphan*/  __INIT_INSTANCE_MEMBERS_java_lang_Object (scalar_t__,int) ; 

void __INIT_INSTANCE_MEMBERS_java_lang_String(JAVA_OBJECT me, int derivedClassWillRegisterFinalizer)
{
    __INIT_INSTANCE_MEMBERS_java_lang_Object(me, 0 || derivedClassWillRegisterFinalizer);
    ((java_lang_String*) me)->fields.java_lang_String.charset_ = (org_apache_harmony_niochar_charset_UTF_8*) JAVA_NULL;
    ((java_lang_String*) me)->fields.java_lang_String.charset2_ = (java_lang_Object*) JAVA_NULL;
    ((java_lang_String*) me)->fields.java_lang_String.charset3_ = (java_lang_Object*) JAVA_NULL;
    ((java_lang_String*) me)->fields.java_lang_String.value_ = (org_xmlvm_runtime_XMLVMArray*) JAVA_NULL;
    ((java_lang_String*) me)->fields.java_lang_String.offset_ = 0;
    ((java_lang_String*) me)->fields.java_lang_String.count_ = 0;
    ((java_lang_String*) me)->fields.java_lang_String.hashCode_ = 0;
    //XMLVM_BEGIN_WRAPPER[__INIT_INSTANCE_MEMBERS_java_lang_String]
    //XMLVM_END_WRAPPER
}