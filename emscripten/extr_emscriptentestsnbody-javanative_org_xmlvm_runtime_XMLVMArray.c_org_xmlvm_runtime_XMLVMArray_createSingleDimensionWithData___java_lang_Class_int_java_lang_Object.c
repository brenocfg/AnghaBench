#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  org_xmlvm_runtime_XMLVMArray ;
struct TYPE_5__ {TYPE_4__* tib_; } ;
struct TYPE_6__ {TYPE_1__ java_lang_Class; } ;
struct TYPE_7__ {TYPE_2__ fields; } ;
typedef  TYPE_3__ java_lang_Class ;
struct TYPE_8__ {scalar_t__ arrayType; } ;
typedef  TYPE_4__ __TIB_DEFINITION_TEMPLATE ;
typedef  scalar_t__ JAVA_OBJECT ;
typedef  int /*<<< orphan*/  JAVA_INT ;

/* Variables and functions */
 scalar_t__ JAVA_NULL ; 
 int /*<<< orphan*/  XMLVM_INTERNAL_ERROR () ; 
 int /*<<< orphan*/ * __NEW_org_xmlvm_runtime_XMLVMArray () ; 
 int /*<<< orphan*/  org_xmlvm_runtime_XMLVMArray___INIT____java_lang_Class_int_java_lang_Object (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 

JAVA_OBJECT org_xmlvm_runtime_XMLVMArray_createSingleDimensionWithData___java_lang_Class_int_java_lang_Object(JAVA_OBJECT n1, JAVA_INT n2, JAVA_OBJECT n3)
{
    //XMLVM_BEGIN_NATIVE[org_xmlvm_runtime_XMLVMArray_createSingleDimensionWithData___java_lang_Class_int_java_lang_Object]
    org_xmlvm_runtime_XMLVMArray* array = __NEW_org_xmlvm_runtime_XMLVMArray();
    java_lang_Class* baseType = n1;
    __TIB_DEFINITION_TEMPLATE* baseTIB = baseType->fields.java_lang_Class.tib_;
    JAVA_OBJECT arrayType = baseTIB->arrayType;
    if (arrayType == JAVA_NULL) {
        XMLVM_INTERNAL_ERROR();
    }
    org_xmlvm_runtime_XMLVMArray___INIT____java_lang_Class_int_java_lang_Object(array, arrayType, n2, n3);
    return array;
    //XMLVM_END_NATIVE
}