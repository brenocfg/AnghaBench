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
typedef  long JAVA_LONG ;

/* Variables and functions */

JAVA_LONG java_lang_System_nanoTime__()
{
    //XMLVM_BEGIN_NATIVE[java_lang_System_nanoTime__]
    //TODO implement
    return java_lang_System_nanoTime__() * 1000000L;
    //XMLVM_END_NATIVE
}