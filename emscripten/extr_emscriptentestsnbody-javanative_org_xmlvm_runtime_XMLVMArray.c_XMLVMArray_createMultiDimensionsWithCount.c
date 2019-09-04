#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ array_; } ;
struct TYPE_12__ {TYPE_1__ org_xmlvm_runtime_XMLVMArray; } ;
struct TYPE_15__ {TYPE_2__ fields; } ;
typedef  TYPE_5__ org_xmlvm_runtime_XMLVMArray ;
struct TYPE_13__ {scalar_t__ tib_; } ;
struct TYPE_14__ {TYPE_3__ java_lang_Class; } ;
struct TYPE_16__ {TYPE_4__ fields; } ;
typedef  TYPE_6__ java_lang_Class ;
struct TYPE_17__ {scalar_t__ baseType; } ;
typedef  TYPE_7__ __TIB_DEFINITION_TEMPLATE ;
typedef  scalar_t__ JAVA_OBJECT ;
typedef  TYPE_5__* JAVA_ARRAY_OBJECT ;
typedef  int JAVA_ARRAY_INT ;

/* Variables and functions */
 TYPE_5__* XMLVMArray_createSingleDimension (scalar_t__,int) ; 

__attribute__((used)) static org_xmlvm_runtime_XMLVMArray* XMLVMArray_createMultiDimensionsWithCount(JAVA_OBJECT type, JAVA_ARRAY_INT* dim, int count)
{
    JAVA_ARRAY_INT dimensions = *dim;
    org_xmlvm_runtime_XMLVMArray* slice;
    int i;
    dim++;
    count--;
    if (count == 0) {
        return XMLVMArray_createSingleDimension(type, dimensions);
    }
    slice = XMLVMArray_createSingleDimension(type, dimensions);
    JAVA_ARRAY_OBJECT* sliceData = (JAVA_ARRAY_OBJECT*) slice->fields.org_xmlvm_runtime_XMLVMArray.array_;
    // Get base type
    java_lang_Class* typeClass = (java_lang_Class*) type;
    __TIB_DEFINITION_TEMPLATE* typeTIB = (__TIB_DEFINITION_TEMPLATE*) typeClass->fields.java_lang_Class.tib_;
    JAVA_OBJECT baseType = typeTIB->baseType;
    for (i = 0; i < dimensions; i++) {
        //TODO should 'type' be baseType of this type?
        sliceData[i] = XMLVMArray_createMultiDimensionsWithCount(baseType, dim, count);
    }
    return slice;
}