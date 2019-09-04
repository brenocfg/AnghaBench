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

JAVA_INT XMLVMUtil_Iterator_next(JAVA_OBJECT me)
{
#ifdef XMLVM_VTABLE_IDX_java_util_Iterator_next__
    return (*(JAVA_INT (*)(JAVA_OBJECT)) ((java_util_Iterator*) me)->
            tib->vtable[XMLVM_VTABLE_IDX_java_util_Iterator_next__])(me);
#endif
}