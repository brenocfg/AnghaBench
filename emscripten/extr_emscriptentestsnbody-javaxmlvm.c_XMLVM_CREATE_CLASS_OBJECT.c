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
 int /*<<< orphan*/  __NEW_java_lang_Class () ; 
 int /*<<< orphan*/  java_lang_Class___INIT____java_lang_Object (int /*<<< orphan*/ ,void*) ; 

JAVA_OBJECT XMLVM_CREATE_CLASS_OBJECT(void* tib)
{
    JAVA_OBJECT clazz = __NEW_java_lang_Class();
    java_lang_Class___INIT____java_lang_Object(clazz, tib);
    return clazz;
}