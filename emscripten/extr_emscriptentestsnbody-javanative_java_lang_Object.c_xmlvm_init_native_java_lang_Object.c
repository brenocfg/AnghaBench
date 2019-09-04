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

void xmlvm_init_native_java_lang_Object()
{
    //XMLVM_BEGIN_NATIVE_IMPLEMENTATION_INIT
    //XMLVM_END_NATIVE_IMPLEMENTATION_INIT
#ifdef XMLVM_VTABLE_IDX_java_lang_Object_clone__
    __TIB_java_lang_Object.vtable[XMLVM_VTABLE_IDX_java_lang_Object_clone__] = 
        (VTABLE_PTR) java_lang_Object_clone__;
#endif
#ifdef XMLVM_VTABLE_IDX_java_lang_Object_equals___java_lang_Object
    __TIB_java_lang_Object.vtable[XMLVM_VTABLE_IDX_java_lang_Object_equals___java_lang_Object] = 
        (VTABLE_PTR) java_lang_Object_equals___java_lang_Object;
#endif
#ifdef XMLVM_VTABLE_IDX_java_lang_Object_finalize_java_lang_Object__
    __TIB_java_lang_Object.vtable[XMLVM_VTABLE_IDX_java_lang_Object_finalize_java_lang_Object__] = 
        (VTABLE_PTR) java_lang_Object_finalize_java_lang_Object__;
#endif
#ifdef XMLVM_VTABLE_IDX_java_lang_Object_getClass__
    __TIB_java_lang_Object.vtable[XMLVM_VTABLE_IDX_java_lang_Object_getClass__] = 
        (VTABLE_PTR) java_lang_Object_getClass__;
#endif
#ifdef XMLVM_VTABLE_IDX_java_lang_Object_hashCode__
    __TIB_java_lang_Object.vtable[XMLVM_VTABLE_IDX_java_lang_Object_hashCode__] = 
        (VTABLE_PTR) java_lang_Object_hashCode__;
#endif
#ifdef XMLVM_VTABLE_IDX_java_lang_Object_wait___long_int
    __TIB_java_lang_Object.vtable[XMLVM_VTABLE_IDX_java_lang_Object_wait___long_int] = 
        (VTABLE_PTR) java_lang_Object_wait___long_int;
#endif
}