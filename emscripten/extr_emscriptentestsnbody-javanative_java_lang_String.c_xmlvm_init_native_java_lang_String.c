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

void xmlvm_init_native_java_lang_String()
{
    //XMLVM_BEGIN_NATIVE_IMPLEMENTATION_INIT
    //XMLVM_END_NATIVE_IMPLEMENTATION_INIT
#ifdef XMLVM_VTABLE_IDX_java_lang_String_toLowerCaseImpl___int
    __TIB_java_lang_String.vtable[XMLVM_VTABLE_IDX_java_lang_String_toLowerCaseImpl___int] = 
        (VTABLE_PTR) java_lang_String_toLowerCaseImpl___int;
#endif
#ifdef XMLVM_VTABLE_IDX_java_lang_String_toUpperCaseImpl___int
    __TIB_java_lang_String.vtable[XMLVM_VTABLE_IDX_java_lang_String_toUpperCaseImpl___int] = 
        (VTABLE_PTR) java_lang_String_toUpperCaseImpl___int;
#endif
}