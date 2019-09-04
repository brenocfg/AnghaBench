#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ type_; scalar_t__ array_; } ;
struct TYPE_5__ {TYPE_1__ org_xmlvm_runtime_XMLVMArray; } ;
struct TYPE_6__ {TYPE_2__ fields; } ;
typedef  TYPE_3__ org_xmlvm_runtime_XMLVMArray ;
typedef  scalar_t__ JAVA_OBJECT ;
typedef  size_t JAVA_INT ;
typedef  scalar_t__ JAVA_ARRAY_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  XMLVM_INTERNAL_ERROR () ; 
 scalar_t__ __CLASS_boolean_1ARRAY ; 
 scalar_t__ __CLASS_byte_1ARRAY ; 
 scalar_t__ __CLASS_char_1ARRAY ; 
 scalar_t__ __CLASS_double_1ARRAY ; 
 scalar_t__ __CLASS_float_1ARRAY ; 
 scalar_t__ __CLASS_int_1ARRAY ; 
 scalar_t__ __CLASS_long_1ARRAY ; 
 scalar_t__ __CLASS_short_1ARRAY ; 

void java_lang_reflect_Array_set___java_lang_Object_int_java_lang_Object(JAVA_OBJECT n1, JAVA_INT n2, JAVA_OBJECT n3)
{
    //XMLVM_BEGIN_NATIVE[java_lang_reflect_Array_set___java_lang_Object_int_java_lang_Object]
    org_xmlvm_runtime_XMLVMArray* array = n1;
    JAVA_INT index = n2;
    JAVA_OBJECT obj = n3;
    
    JAVA_OBJECT arrayType = array->fields.org_xmlvm_runtime_XMLVMArray.type_;
    if (arrayType == __CLASS_boolean_1ARRAY) {
        XMLVM_INTERNAL_ERROR();
    } else if (arrayType == __CLASS_byte_1ARRAY) {
        XMLVM_INTERNAL_ERROR();
    } else if (arrayType == __CLASS_char_1ARRAY) {
        XMLVM_INTERNAL_ERROR();
    } else if (arrayType == __CLASS_short_1ARRAY) {
        XMLVM_INTERNAL_ERROR();
    } else if (arrayType == __CLASS_int_1ARRAY) {
        XMLVM_INTERNAL_ERROR();
    } else if (arrayType == __CLASS_float_1ARRAY) {
        XMLVM_INTERNAL_ERROR();
    } else if (arrayType == __CLASS_long_1ARRAY) {
        XMLVM_INTERNAL_ERROR();
    } else if (arrayType == __CLASS_double_1ARRAY) {
        XMLVM_INTERNAL_ERROR();
    } else {
        JAVA_ARRAY_OBJECT* data = (JAVA_ARRAY_OBJECT*) array->fields.org_xmlvm_runtime_XMLVMArray.array_;
        data[index] = obj;
    }
    //XMLVM_END_NATIVE
}