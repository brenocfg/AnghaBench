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
 int /*<<< orphan*/  GC_gcollect () ; 

void java_lang_Runtime_gc__(JAVA_OBJECT me)
{
    //XMLVM_BEGIN_NATIVE[java_lang_Runtime_gc__]
#ifndef XMLVM_NO_GC
    GC_gcollect();
#endif
    //XMLVM_END_NATIVE
}