#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {scalar_t__ type_; int length_; scalar_t__ array_; } ;
struct TYPE_17__ {TYPE_4__ org_xmlvm_runtime_XMLVMArray; } ;
struct TYPE_19__ {TYPE_3__ fields; } ;
typedef  TYPE_5__ org_xmlvm_runtime_XMLVMArray ;
struct TYPE_15__ {TYPE_7__* tib_; } ;
struct TYPE_16__ {TYPE_1__ java_lang_Class; } ;
struct TYPE_20__ {TYPE_2__ fields; } ;
typedef  TYPE_6__ java_lang_Class ;
struct TYPE_21__ {TYPE_6__* arrayType; } ;
typedef  TYPE_7__ __TIB_DEFINITION_TEMPLATE ;
typedef  TYPE_6__* JAVA_OBJECT ;
typedef  int /*<<< orphan*/  JAVA_ARRAY_INT ;

/* Variables and functions */
 TYPE_6__* JAVA_NULL ; 
 TYPE_6__* XMLVMArray_createMultiDimensionsWithCount (TYPE_6__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  XMLVM_INTERNAL_ERROR () ; 
 scalar_t__ __CLASS_int_1ARRAY ; 

JAVA_OBJECT org_xmlvm_runtime_XMLVMArray_createMultiDimensions___java_lang_Class_org_xmlvm_runtime_XMLVMArray(JAVA_OBJECT n1, JAVA_OBJECT n2)
{
    //XMLVM_BEGIN_NATIVE[org_xmlvm_runtime_XMLVMArray_createMultiDimensions___java_lang_Class_org_xmlvm_runtime_XMLVMArray]
    org_xmlvm_runtime_XMLVMArray* dimArray = (org_xmlvm_runtime_XMLVMArray*) n2;
    if (dimArray->fields.org_xmlvm_runtime_XMLVMArray.type_ != __CLASS_int_1ARRAY) {
        XMLVM_INTERNAL_ERROR();
    }
    int count = dimArray->fields.org_xmlvm_runtime_XMLVMArray.length_;
    JAVA_ARRAY_INT* data = (JAVA_ARRAY_INT*) dimArray->fields.org_xmlvm_runtime_XMLVMArray.array_;
    int i;
    java_lang_Class* arrayType = n1;
    for (i = 0; i < count - 1; i++) {
        __TIB_DEFINITION_TEMPLATE* arrayTIB = arrayType->fields.java_lang_Class.tib_;
        arrayType = arrayTIB->arrayType;
        if (arrayType == JAVA_NULL) {
            XMLVM_INTERNAL_ERROR();
        }
    }
    return XMLVMArray_createMultiDimensionsWithCount(arrayType, data, count);
    //XMLVM_END_NATIVE
}