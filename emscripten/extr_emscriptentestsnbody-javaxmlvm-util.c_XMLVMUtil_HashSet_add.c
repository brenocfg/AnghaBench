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
typedef  int /*<<< orphan*/  JAVA_BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  java_util_HashSet_add___java_lang_Object (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

JAVA_BOOLEAN XMLVMUtil_HashSet_add(JAVA_OBJECT me, JAVA_OBJECT obj)
{
#ifdef XMLVM_VTABLE_IDX_java_util_HashSet_add___java_lang_Object
    return (*(JAVA_BOOLEAN (*)(JAVA_OBJECT, JAVA_OBJECT)) ((java_util_HashSet*) me)->
            tib->vtable[XMLVM_VTABLE_IDX_java_util_HashSet_add___java_lang_Object])(me, obj);
#else
    return java_util_HashSet_add___java_lang_Object(me, obj);
#endif
}