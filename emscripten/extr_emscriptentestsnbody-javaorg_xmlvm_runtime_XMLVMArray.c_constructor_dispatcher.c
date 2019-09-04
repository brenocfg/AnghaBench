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
struct TYPE_12__ {scalar_t__ array_; } ;
struct TYPE_13__ {TYPE_3__ org_xmlvm_runtime_XMLVMArray; } ;
struct TYPE_16__ {TYPE_4__ fields; } ;
typedef  TYPE_7__ org_xmlvm_runtime_XMLVMArray ;
struct TYPE_15__ {int slot_; } ;
struct TYPE_14__ {TYPE_6__ java_lang_reflect_Constructor; } ;
struct TYPE_17__ {TYPE_5__ fields; } ;
typedef  TYPE_8__ java_lang_reflect_Constructor ;
struct TYPE_10__ {int /*<<< orphan*/  value_; } ;
struct TYPE_11__ {TYPE_1__ java_lang_Integer; } ;
struct TYPE_18__ {TYPE_2__ fields; } ;
typedef  TYPE_9__ java_lang_Integer ;
typedef  scalar_t__ JAVA_OBJECT ;
typedef  scalar_t__ JAVA_ARRAY_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  XMLVM_INTERNAL_ERROR () ; 
 scalar_t__ __NEW_org_xmlvm_runtime_XMLVMArray () ; 
 int /*<<< orphan*/  org_xmlvm_runtime_XMLVMArray___INIT____java_lang_Class_int_java_lang_Object (scalar_t__,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static JAVA_OBJECT constructor_dispatcher(JAVA_OBJECT constructor, JAVA_OBJECT arguments)
{
    JAVA_OBJECT obj = __NEW_org_xmlvm_runtime_XMLVMArray();
    java_lang_reflect_Constructor* c = (java_lang_reflect_Constructor*) constructor;
    org_xmlvm_runtime_XMLVMArray* args = (org_xmlvm_runtime_XMLVMArray*) arguments;
    JAVA_ARRAY_OBJECT* argsArray = (JAVA_ARRAY_OBJECT*) args->fields.org_xmlvm_runtime_XMLVMArray.array_;
    switch (c->fields.java_lang_reflect_Constructor.slot_) {
    case 0:
        org_xmlvm_runtime_XMLVMArray___INIT____java_lang_Class_int_java_lang_Object(obj, argsArray[0], ((java_lang_Integer*) argsArray[1])->fields.java_lang_Integer.value_, argsArray[2]);
        break;
    default:
        XMLVM_INTERNAL_ERROR();
        break;
    }
    return obj;
}