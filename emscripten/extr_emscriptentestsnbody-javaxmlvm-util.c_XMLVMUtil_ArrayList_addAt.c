#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  JAVA_OBJECT ;
typedef  int /*<<< orphan*/  JAVA_INT ;

/* Variables and functions */
 int /*<<< orphan*/  java_util_ArrayList_add___int_java_lang_Object (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void XMLVMUtil_ArrayList_addAt(JAVA_OBJECT me, JAVA_INT index, JAVA_OBJECT obj)
{
#ifdef XMLVM_VTABLE_IDX_java_util_ArrayList_add___int_java_lang_Object
    (*(JAVA_BOOLEAN (*)(JAVA_OBJECT, JAVA_INT, JAVA_OBJECT)) ((java_util_ArrayList*) me)->
            tib->vtable[XMLVM_VTABLE_IDX_java_util_ArrayList_add___int_java_lang_Object])(me, index, obj);
#else
    java_util_ArrayList_add___int_java_lang_Object(me, index, obj);
#endif
}