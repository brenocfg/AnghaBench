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

/* Variables and functions */
 int /*<<< orphan*/  java_util_HashMap_entrySet__ (int /*<<< orphan*/ ) ; 

JAVA_OBJECT XMLVMUtil_HashMap_entrySet(JAVA_OBJECT me)
{
#ifdef XMLVM_VTABLE_IDX_java_util_HashMap_entrySet__
    return (*(JAVA_OBJECT (*)(JAVA_OBJECT)) ((java_util_HashMap*) me)->
            tib->vtable[XMLVM_VTABLE_IDX_java_util_HashMap_entrySet__])(me);
#else
	return java_util_HashMap_entrySet__(me);
#endif
}