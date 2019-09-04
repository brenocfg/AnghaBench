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
 int /*<<< orphan*/  java_util_HashSet_iterator__ (int /*<<< orphan*/ ) ; 

JAVA_INT XMLVMUtil_HashSet_iterator(JAVA_OBJECT me)
{
#ifdef XMLVM_VTABLE_IDX_java_util_HashSet_iterator__
    return (*(JAVA_INT (*)(JAVA_OBJECT)) ((java_util_HashSet*) me)->
            tib->vtable[XMLVM_ITABLE_IDX_java_util_Set_iterator__])(me);
#else
    return java_util_HashSet_iterator__(me);
#endif
}