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

/* Variables and functions */
 void* XMLVM_CREATE_ARRAY_CLASS_OBJECT (void*) ; 
 void* XMLVM_CREATE_CLASS_OBJECT (int /*<<< orphan*/ *) ; 
 void* __CLASS_boolean ; 
 void* __CLASS_boolean_1ARRAY ; 
 void* __CLASS_boolean_2ARRAY ; 
 void* __CLASS_boolean_3ARRAY ; 
 void* __CLASS_byte ; 
 void* __CLASS_byte_1ARRAY ; 
 void* __CLASS_byte_2ARRAY ; 
 void* __CLASS_byte_3ARRAY ; 
 void* __CLASS_char ; 
 void* __CLASS_char_1ARRAY ; 
 void* __CLASS_char_2ARRAY ; 
 void* __CLASS_char_3ARRAY ; 
 void* __CLASS_double ; 
 void* __CLASS_double_1ARRAY ; 
 void* __CLASS_double_2ARRAY ; 
 void* __CLASS_double_3ARRAY ; 
 void* __CLASS_float ; 
 void* __CLASS_float_1ARRAY ; 
 void* __CLASS_float_2ARRAY ; 
 void* __CLASS_float_3ARRAY ; 
 void* __CLASS_int ; 
 void* __CLASS_int_1ARRAY ; 
 void* __CLASS_int_2ARRAY ; 
 void* __CLASS_int_3ARRAY ; 
 void* __CLASS_long ; 
 void* __CLASS_long_1ARRAY ; 
 void* __CLASS_long_2ARRAY ; 
 void* __CLASS_long_3ARRAY ; 
 void* __CLASS_short ; 
 void* __CLASS_short_1ARRAY ; 
 void* __CLASS_short_2ARRAY ; 
 void* __CLASS_short_3ARRAY ; 
 void* __CLASS_void ; 
 int /*<<< orphan*/  __INIT_boolean () ; 
 int /*<<< orphan*/  __INIT_byte () ; 
 int /*<<< orphan*/  __INIT_char () ; 
 int /*<<< orphan*/  __INIT_double () ; 
 int /*<<< orphan*/  __INIT_float () ; 
 int /*<<< orphan*/  __INIT_int () ; 
 int /*<<< orphan*/  __INIT_long () ; 
 int /*<<< orphan*/  __INIT_short () ; 
 int /*<<< orphan*/  __INIT_void () ; 
 int /*<<< orphan*/  __TIB_boolean ; 
 int /*<<< orphan*/  __TIB_byte ; 
 int /*<<< orphan*/  __TIB_char ; 
 int /*<<< orphan*/  __TIB_double ; 
 int /*<<< orphan*/  __TIB_float ; 
 int /*<<< orphan*/  __TIB_int ; 
 int /*<<< orphan*/  __TIB_long ; 
 int /*<<< orphan*/  __TIB_short ; 
 int /*<<< orphan*/  __TIB_void ; 

void java_lang_Class_initNativeLayer__()
{
    //XMLVM_BEGIN_NATIVE[java_lang_Class_initNativeLayer__]
    __INIT_boolean();
    __INIT_byte();
    __INIT_char();
    __INIT_short();
    __INIT_int();
    __INIT_long();
    __INIT_float();
    __INIT_double();
    __INIT_void();
    
    __CLASS_boolean = XMLVM_CREATE_CLASS_OBJECT(&__TIB_boolean);
    __CLASS_byte = XMLVM_CREATE_CLASS_OBJECT(&__TIB_byte);
    __CLASS_char = XMLVM_CREATE_CLASS_OBJECT(&__TIB_char);
    __CLASS_short = XMLVM_CREATE_CLASS_OBJECT(&__TIB_short);
    __CLASS_int = XMLVM_CREATE_CLASS_OBJECT(&__TIB_int);
    __CLASS_long = XMLVM_CREATE_CLASS_OBJECT(&__TIB_long);
    __CLASS_float = XMLVM_CREATE_CLASS_OBJECT(&__TIB_float);
    __CLASS_double = XMLVM_CREATE_CLASS_OBJECT(&__TIB_double);
    __CLASS_void = XMLVM_CREATE_CLASS_OBJECT(&__TIB_void);
    
    __CLASS_boolean_1ARRAY = XMLVM_CREATE_ARRAY_CLASS_OBJECT(__CLASS_boolean);
    __CLASS_byte_1ARRAY = XMLVM_CREATE_ARRAY_CLASS_OBJECT(__CLASS_byte);
    __CLASS_char_1ARRAY = XMLVM_CREATE_ARRAY_CLASS_OBJECT(__CLASS_char);
    __CLASS_short_1ARRAY = XMLVM_CREATE_ARRAY_CLASS_OBJECT(__CLASS_short);
    __CLASS_int_1ARRAY = XMLVM_CREATE_ARRAY_CLASS_OBJECT(__CLASS_int);
    __CLASS_long_1ARRAY = XMLVM_CREATE_ARRAY_CLASS_OBJECT(__CLASS_long);
    __CLASS_float_1ARRAY = XMLVM_CREATE_ARRAY_CLASS_OBJECT(__CLASS_float);
    __CLASS_double_1ARRAY = XMLVM_CREATE_ARRAY_CLASS_OBJECT(__CLASS_double);
    
    __CLASS_boolean_2ARRAY = XMLVM_CREATE_ARRAY_CLASS_OBJECT(__CLASS_boolean_1ARRAY);
    __CLASS_byte_2ARRAY = XMLVM_CREATE_ARRAY_CLASS_OBJECT(__CLASS_byte_1ARRAY);
    __CLASS_char_2ARRAY = XMLVM_CREATE_ARRAY_CLASS_OBJECT(__CLASS_char_1ARRAY);
    __CLASS_short_2ARRAY = XMLVM_CREATE_ARRAY_CLASS_OBJECT(__CLASS_short_1ARRAY);
    __CLASS_int_2ARRAY = XMLVM_CREATE_ARRAY_CLASS_OBJECT(__CLASS_int_1ARRAY);
    __CLASS_long_2ARRAY = XMLVM_CREATE_ARRAY_CLASS_OBJECT(__CLASS_long_1ARRAY);
    __CLASS_float_2ARRAY = XMLVM_CREATE_ARRAY_CLASS_OBJECT(__CLASS_float_1ARRAY);
    __CLASS_double_2ARRAY = XMLVM_CREATE_ARRAY_CLASS_OBJECT(__CLASS_double_1ARRAY);
    
    __CLASS_boolean_3ARRAY = XMLVM_CREATE_ARRAY_CLASS_OBJECT(__CLASS_boolean_2ARRAY);
    __CLASS_byte_3ARRAY = XMLVM_CREATE_ARRAY_CLASS_OBJECT(__CLASS_byte_2ARRAY);
    __CLASS_char_3ARRAY = XMLVM_CREATE_ARRAY_CLASS_OBJECT(__CLASS_char_2ARRAY);
    __CLASS_short_3ARRAY = XMLVM_CREATE_ARRAY_CLASS_OBJECT(__CLASS_short_2ARRAY);
    __CLASS_int_3ARRAY = XMLVM_CREATE_ARRAY_CLASS_OBJECT(__CLASS_int_2ARRAY);
    __CLASS_long_3ARRAY = XMLVM_CREATE_ARRAY_CLASS_OBJECT(__CLASS_long_2ARRAY);
    __CLASS_float_3ARRAY = XMLVM_CREATE_ARRAY_CLASS_OBJECT(__CLASS_float_2ARRAY);
    __CLASS_double_3ARRAY = XMLVM_CREATE_ARRAY_CLASS_OBJECT(__CLASS_double_2ARRAY);
    //XMLVM_END_NATIVE
}