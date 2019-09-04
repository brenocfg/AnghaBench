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
struct TYPE_4__ {scalar_t__ type_; int modifiers_; int offset_; scalar_t__ address_; } ;
struct TYPE_5__ {TYPE_1__ java_lang_reflect_Field; } ;
struct TYPE_6__ {TYPE_2__ fields; } ;
typedef  TYPE_3__ java_lang_reflect_Field ;
typedef  int /*<<< orphan*/  JAVA_SHORT ;
typedef  scalar_t__ JAVA_OBJECT ;
typedef  int /*<<< orphan*/  JAVA_LONG ;
typedef  int /*<<< orphan*/  JAVA_INT ;
typedef  int /*<<< orphan*/  JAVA_FLOAT ;
typedef  int /*<<< orphan*/  JAVA_DOUBLE ;
typedef  int /*<<< orphan*/  JAVA_CHAR ;
typedef  int /*<<< orphan*/  JAVA_BYTE ;
typedef  int /*<<< orphan*/  JAVA_BOOLEAN ;

/* Variables and functions */
 scalar_t__ __CLASS_boolean ; 
 scalar_t__ __CLASS_byte ; 
 scalar_t__ __CLASS_char ; 
 scalar_t__ __CLASS_double ; 
 scalar_t__ __CLASS_float ; 
 scalar_t__ __CLASS_int ; 
 scalar_t__ __CLASS_long ; 
 scalar_t__ __CLASS_short ; 
 scalar_t__ __NEW_java_lang_Boolean () ; 
 scalar_t__ __NEW_java_lang_Byte () ; 
 scalar_t__ __NEW_java_lang_Character () ; 
 scalar_t__ __NEW_java_lang_Double () ; 
 scalar_t__ __NEW_java_lang_Float () ; 
 scalar_t__ __NEW_java_lang_Integer () ; 
 scalar_t__ __NEW_java_lang_Long () ; 
 scalar_t__ __NEW_java_lang_Short () ; 
 int /*<<< orphan*/  java_lang_Boolean___INIT____boolean (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  java_lang_Byte___INIT____byte (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  java_lang_Character___INIT____char (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  java_lang_Double___INIT____double (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  java_lang_Float___INIT____float (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  java_lang_Integer___INIT____int (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  java_lang_Long___INIT____long (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  java_lang_Short___INIT____short (scalar_t__,int /*<<< orphan*/ ) ; 
 int java_lang_reflect_Modifier_STATIC ; 

JAVA_OBJECT java_lang_reflect_Field_get___java_lang_Object(JAVA_OBJECT me, JAVA_OBJECT n1)
{
    //XMLVM_BEGIN_NATIVE[java_lang_reflect_Field_get___java_lang_Object]
    java_lang_reflect_Field* thiz = (java_lang_reflect_Field*) me;
    JAVA_OBJECT type = thiz->fields.java_lang_reflect_Field.type_;
    char* valuePtr;
    if (thiz->fields.java_lang_reflect_Field.modifiers_ & java_lang_reflect_Modifier_STATIC) {
        valuePtr = (char*) thiz->fields.java_lang_reflect_Field.address_;
    } else {
        valuePtr = ((char*) n1) + thiz->fields.java_lang_reflect_Field.offset_;
    }
    JAVA_OBJECT obj;
    if (type == __CLASS_boolean) {
        JAVA_BOOLEAN value = *((JAVA_BOOLEAN*) valuePtr);
        obj = __NEW_java_lang_Boolean();
        java_lang_Boolean___INIT____boolean(obj, value);
    } else if (type == __CLASS_byte) {
        JAVA_BYTE value = *((JAVA_BYTE*) valuePtr);
        obj = __NEW_java_lang_Byte();
        java_lang_Byte___INIT____byte(obj, value);
    } else if (type == __CLASS_char) {
        JAVA_CHAR value = *((JAVA_CHAR*) valuePtr);
        obj = __NEW_java_lang_Character();
        java_lang_Character___INIT____char(obj, value);
    } else if (type == __CLASS_short) {
        JAVA_SHORT value = *((JAVA_SHORT*) valuePtr);
        obj = __NEW_java_lang_Short();
        java_lang_Short___INIT____short(obj, value);
    } else if (type == __CLASS_int) {
        JAVA_INT value = *((JAVA_INT*) valuePtr);
        obj = __NEW_java_lang_Integer();
        java_lang_Integer___INIT____int(obj, value);
    } else if (type == __CLASS_long) {
        JAVA_LONG value = *((JAVA_LONG*) valuePtr);
        obj = __NEW_java_lang_Long();
        java_lang_Long___INIT____long(obj, value);
    } else if (type == __CLASS_float) {
        JAVA_FLOAT value = *((JAVA_FLOAT*) valuePtr);
        obj = __NEW_java_lang_Float();
        java_lang_Float___INIT____float(obj, value);
    } else if (type == __CLASS_double) {
        JAVA_DOUBLE value = *((JAVA_DOUBLE*) valuePtr);
        obj = __NEW_java_lang_Double();
        java_lang_Double___INIT____double(obj, value);
    } else {
        // Has to be object type if it is not a primitive type
        obj = *((JAVA_OBJECT*) valuePtr);
    }
    return obj;
    //XMLVM_END_NATIVE
}