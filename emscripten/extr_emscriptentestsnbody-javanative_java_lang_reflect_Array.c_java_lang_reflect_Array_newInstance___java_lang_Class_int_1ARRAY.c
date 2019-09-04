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
 int /*<<< orphan*/  XMLVMArray_createMultiDimensions (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

JAVA_OBJECT java_lang_reflect_Array_newInstance___java_lang_Class_int_1ARRAY(JAVA_OBJECT n1, JAVA_OBJECT n2)
{
    //XMLVM_BEGIN_NATIVE[java_lang_reflect_Array_newInstance___java_lang_Class_int_1ARRAY]
    return XMLVMArray_createMultiDimensions(n1, n2);
    //XMLVM_END_NATIVE
}