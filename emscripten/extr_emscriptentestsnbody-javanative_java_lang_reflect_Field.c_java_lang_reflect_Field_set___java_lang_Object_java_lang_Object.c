#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ type_; } ;
struct TYPE_6__ {TYPE_1__ java_lang_reflect_Field; } ;
struct TYPE_7__ {TYPE_2__ fields; } ;
typedef  TYPE_3__ java_lang_reflect_Field ;
typedef  scalar_t__ JAVA_OBJECT ;

/* Variables and functions */
 char* VALUE_PTR (TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (char*,scalar_t__*,int) ; 

void java_lang_reflect_Field_set___java_lang_Object_java_lang_Object(JAVA_OBJECT me, JAVA_OBJECT n1, JAVA_OBJECT n2)
{
    //XMLVM_BEGIN_NATIVE[java_lang_reflect_Field_set___java_lang_Object_java_lang_Object]
    java_lang_reflect_Field* thiz = (java_lang_reflect_Field*) me;
    JAVA_OBJECT type = thiz->fields.java_lang_reflect_Field.type_;
    char* valuePtr=VALUE_PTR(thiz, n2);
    memcpy(valuePtr, &n1, 4);
    //XMLVM_END_NATIVE
}