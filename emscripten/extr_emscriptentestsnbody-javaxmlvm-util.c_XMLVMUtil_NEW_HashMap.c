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
 int /*<<< orphan*/  __NEW_java_util_HashMap () ; 
 int /*<<< orphan*/  java_util_HashMap___INIT___ (int /*<<< orphan*/ ) ; 

JAVA_OBJECT XMLVMUtil_NEW_HashMap()
{
    JAVA_OBJECT obj = __NEW_java_util_HashMap();
    java_util_HashMap___INIT___(obj);
    return obj;
}