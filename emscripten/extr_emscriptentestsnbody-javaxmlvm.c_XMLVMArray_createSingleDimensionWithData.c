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
 int /*<<< orphan*/  org_xmlvm_runtime_XMLVMArray_createSingleDimensionWithData___java_lang_Class_int_java_lang_Object (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

JAVA_OBJECT XMLVMArray_createSingleDimensionWithData(JAVA_OBJECT type, JAVA_INT size, JAVA_OBJECT data)
{
    return org_xmlvm_runtime_XMLVMArray_createSingleDimensionWithData___java_lang_Class_int_java_lang_Object(type, size, data);
}