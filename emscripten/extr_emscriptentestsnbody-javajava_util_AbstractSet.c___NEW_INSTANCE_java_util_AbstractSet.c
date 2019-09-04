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
 int /*<<< orphan*/  JAVA_NULL ; 
 int /*<<< orphan*/  __NEW_java_util_AbstractSet () ; 
 int /*<<< orphan*/  java_util_AbstractSet___INIT___ (int /*<<< orphan*/ ) ; 

JAVA_OBJECT __NEW_INSTANCE_java_util_AbstractSet()
{
    JAVA_OBJECT me = JAVA_NULL;
    me = __NEW_java_util_AbstractSet();
    java_util_AbstractSet___INIT___(me);
    return me;
}