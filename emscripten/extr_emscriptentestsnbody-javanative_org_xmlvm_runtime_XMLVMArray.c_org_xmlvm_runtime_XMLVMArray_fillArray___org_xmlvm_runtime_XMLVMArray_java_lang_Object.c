#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int length_; int /*<<< orphan*/  array_; TYPE_6__* type_; } ;
struct TYPE_11__ {TYPE_1__ org_xmlvm_runtime_XMLVMArray; } ;
struct TYPE_14__ {TYPE_2__ fields; } ;
typedef  TYPE_5__ org_xmlvm_runtime_XMLVMArray ;
struct TYPE_12__ {TYPE_7__* tib_; } ;
struct TYPE_13__ {TYPE_3__ java_lang_Class; } ;
struct TYPE_15__ {TYPE_4__ fields; } ;
typedef  TYPE_6__ java_lang_Class ;
struct TYPE_16__ {int /*<<< orphan*/  baseType; } ;
typedef  TYPE_7__ __TIB_DEFINITION_TEMPLATE ;
struct TYPE_17__ {int sizeOfBaseType; } ;
typedef  TYPE_8__ TYPE_INFO ;
typedef  scalar_t__ JAVA_OBJECT ;

/* Variables and functions */
 TYPE_8__ XMLVMArray_getTypeInfo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XMLVM_MEMCPY (int /*<<< orphan*/ ,scalar_t__,int) ; 

void org_xmlvm_runtime_XMLVMArray_fillArray___org_xmlvm_runtime_XMLVMArray_java_lang_Object(JAVA_OBJECT n1, JAVA_OBJECT n2)
{
    //XMLVM_BEGIN_NATIVE[org_xmlvm_runtime_XMLVMArray_fillArray___org_xmlvm_runtime_XMLVMArray_java_lang_Object]
    org_xmlvm_runtime_XMLVMArray* array = (org_xmlvm_runtime_XMLVMArray*) n1;
    java_lang_Class* arrayType = array->fields.org_xmlvm_runtime_XMLVMArray.type_;
    __TIB_DEFINITION_TEMPLATE* arrayTIB = arrayType->fields.java_lang_Class.tib_;
    TYPE_INFO info = XMLVMArray_getTypeInfo(arrayTIB->baseType);
    int n = info.sizeOfBaseType * array->fields.org_xmlvm_runtime_XMLVMArray.length_;
    XMLVM_MEMCPY(array->fields.org_xmlvm_runtime_XMLVMArray.array_, n2, n);
    //XMLVM_END_NATIVE
}