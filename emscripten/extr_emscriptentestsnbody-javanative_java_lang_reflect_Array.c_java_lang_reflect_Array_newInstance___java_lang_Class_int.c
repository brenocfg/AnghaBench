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
 int /*<<< orphan*/  XMLVMArray_createSingleDimension (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

JAVA_OBJECT java_lang_reflect_Array_newInstance___java_lang_Class_int(JAVA_OBJECT n1, JAVA_INT n2)
{
    //XMLVM_BEGIN_NATIVE[java_lang_reflect_Array_newInstance___java_lang_Class_int]
    return XMLVMArray_createSingleDimension(n1, n2);
    //XMLVM_END_NATIVE
}