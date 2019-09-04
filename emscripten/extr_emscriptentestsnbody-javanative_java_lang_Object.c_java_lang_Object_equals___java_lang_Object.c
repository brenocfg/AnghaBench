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
typedef  scalar_t__ JAVA_OBJECT ;
typedef  int JAVA_BOOLEAN ;

/* Variables and functions */

JAVA_BOOLEAN java_lang_Object_equals___java_lang_Object(JAVA_OBJECT me, JAVA_OBJECT n1)
{
    //XMLVM_BEGIN_NATIVE[java_lang_Object_equals___java_lang_Object]
    return me == n1;
    //XMLVM_END_NATIVE
}