#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ array_; } ;
struct TYPE_11__ {TYPE_1__ org_xmlvm_runtime_XMLVMArray; } ;
struct TYPE_16__ {TYPE_2__ fields; } ;
typedef  TYPE_7__ org_xmlvm_runtime_XMLVMArray ;
struct TYPE_12__ {int slot_; } ;
struct TYPE_13__ {TYPE_3__ java_lang_reflect_Method; } ;
struct TYPE_17__ {TYPE_4__ fields; } ;
typedef  TYPE_8__ java_lang_reflect_Method ;
typedef  int /*<<< orphan*/  java_lang_Object ;
struct TYPE_14__ {int /*<<< orphan*/  value_; } ;
struct TYPE_15__ {TYPE_5__ java_lang_Integer; } ;
struct TYPE_18__ {TYPE_6__ fields; } ;
typedef  TYPE_9__ java_lang_Integer ;
typedef  int /*<<< orphan*/  XMLVMElem ;
typedef  int /*<<< orphan*/ * JAVA_OBJECT ;
typedef  scalar_t__ JAVA_ARRAY_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/ * JAVA_NULL ; 
 int /*<<< orphan*/  XMLVM_INTERNAL_ERROR () ; 
 int /*<<< orphan*/  org_xmlvm_runtime_XMLVMArray_clone__ (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  org_xmlvm_runtime_XMLVMArray_createMultiDimensions___java_lang_Class_org_xmlvm_runtime_XMLVMArray (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  org_xmlvm_runtime_XMLVMArray_createSingleDimensionWithData___java_lang_Class_int_java_lang_Object (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  org_xmlvm_runtime_XMLVMArray_createSingleDimension___java_lang_Class_int (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  org_xmlvm_runtime_XMLVMArray_fillArray___org_xmlvm_runtime_XMLVMArray_java_lang_Object (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  org_xmlvm_runtime_XMLVMArray_initNativeLayer__ () ; 

__attribute__((used)) static JAVA_OBJECT method_dispatcher(JAVA_OBJECT method, JAVA_OBJECT receiver, JAVA_OBJECT arguments)
{
    JAVA_OBJECT result = JAVA_NULL;
    java_lang_Object* obj = receiver;
    java_lang_reflect_Method* m = (java_lang_reflect_Method*) method;
    org_xmlvm_runtime_XMLVMArray* args = (org_xmlvm_runtime_XMLVMArray*) arguments;
    JAVA_ARRAY_OBJECT* argsArray = (JAVA_ARRAY_OBJECT*) args->fields.org_xmlvm_runtime_XMLVMArray.array_;
    XMLVMElem conversion;
    switch (m->fields.java_lang_reflect_Method.slot_) {
    case 0:
        org_xmlvm_runtime_XMLVMArray_initNativeLayer__();
        break;
    case 1:
        result = (JAVA_OBJECT) org_xmlvm_runtime_XMLVMArray_createSingleDimension___java_lang_Class_int(argsArray[0], ((java_lang_Integer*) argsArray[1])->fields.java_lang_Integer.value_);
        break;
    case 2:
        result = (JAVA_OBJECT) org_xmlvm_runtime_XMLVMArray_createSingleDimensionWithData___java_lang_Class_int_java_lang_Object(argsArray[0], ((java_lang_Integer*) argsArray[1])->fields.java_lang_Integer.value_, argsArray[2]);
        break;
    case 3:
        result = (JAVA_OBJECT) org_xmlvm_runtime_XMLVMArray_createMultiDimensions___java_lang_Class_org_xmlvm_runtime_XMLVMArray(argsArray[0], argsArray[1]);
        break;
    case 4:
        org_xmlvm_runtime_XMLVMArray_fillArray___org_xmlvm_runtime_XMLVMArray_java_lang_Object(argsArray[0], argsArray[1]);
        break;
    case 5:
        result = (JAVA_OBJECT) org_xmlvm_runtime_XMLVMArray_clone__(receiver);
        break;
    default:
        XMLVM_INTERNAL_ERROR();
        break;
    }
    return result;
}