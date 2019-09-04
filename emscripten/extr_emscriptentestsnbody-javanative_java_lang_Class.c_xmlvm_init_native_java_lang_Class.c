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

void xmlvm_init_native_java_lang_Class()
{
    //XMLVM_BEGIN_NATIVE_IMPLEMENTATION_INIT
    //XMLVM_END_NATIVE_IMPLEMENTATION_INIT
#ifdef XMLVM_VTABLE_IDX_java_lang_Class_getClasses__
    __TIB_java_lang_Class.vtable[XMLVM_VTABLE_IDX_java_lang_Class_getClasses__] = 
        (VTABLE_PTR) java_lang_Class_getClasses__;
#endif
#ifdef XMLVM_VTABLE_IDX_java_lang_Class_verify__
    __TIB_java_lang_Class.vtable[XMLVM_VTABLE_IDX_java_lang_Class_verify__] = 
        (VTABLE_PTR) java_lang_Class_verify__;
#endif
#ifdef XMLVM_VTABLE_IDX_java_lang_Class_getAnnotation___java_lang_Class
    __TIB_java_lang_Class.vtable[XMLVM_VTABLE_IDX_java_lang_Class_getAnnotation___java_lang_Class] = 
        (VTABLE_PTR) java_lang_Class_getAnnotation___java_lang_Class;
#endif
#ifdef XMLVM_VTABLE_IDX_java_lang_Class_getAnnotations__
    __TIB_java_lang_Class.vtable[XMLVM_VTABLE_IDX_java_lang_Class_getAnnotations__] = 
        (VTABLE_PTR) java_lang_Class_getAnnotations__;
#endif
#ifdef XMLVM_VTABLE_IDX_java_lang_Class_getComponentType__
    __TIB_java_lang_Class.vtable[XMLVM_VTABLE_IDX_java_lang_Class_getComponentType__] = 
        (VTABLE_PTR) java_lang_Class_getComponentType__;
#endif
#ifdef XMLVM_VTABLE_IDX_java_lang_Class_getConstructors__
    __TIB_java_lang_Class.vtable[XMLVM_VTABLE_IDX_java_lang_Class_getConstructors__] = 
        (VTABLE_PTR) java_lang_Class_getConstructors__;
#endif
#ifdef XMLVM_VTABLE_IDX_java_lang_Class_getDeclaredAnnotations__
    __TIB_java_lang_Class.vtable[XMLVM_VTABLE_IDX_java_lang_Class_getDeclaredAnnotations__] = 
        (VTABLE_PTR) java_lang_Class_getDeclaredAnnotations__;
#endif
#ifdef XMLVM_VTABLE_IDX_java_lang_Class_getDeclaredClasses__
    __TIB_java_lang_Class.vtable[XMLVM_VTABLE_IDX_java_lang_Class_getDeclaredClasses__] = 
        (VTABLE_PTR) java_lang_Class_getDeclaredClasses__;
#endif
#ifdef XMLVM_VTABLE_IDX_java_lang_Class_getDeclaredConstructors__
    __TIB_java_lang_Class.vtable[XMLVM_VTABLE_IDX_java_lang_Class_getDeclaredConstructors__] = 
        (VTABLE_PTR) java_lang_Class_getDeclaredConstructors__;
#endif
#ifdef XMLVM_VTABLE_IDX_java_lang_Class_getDeclaredField___java_lang_String
    __TIB_java_lang_Class.vtable[XMLVM_VTABLE_IDX_java_lang_Class_getDeclaredField___java_lang_String] = 
        (VTABLE_PTR) java_lang_Class_getDeclaredField___java_lang_String;
#endif
#ifdef XMLVM_VTABLE_IDX_java_lang_Class_getDeclaredFields__
    __TIB_java_lang_Class.vtable[XMLVM_VTABLE_IDX_java_lang_Class_getDeclaredFields__] = 
        (VTABLE_PTR) java_lang_Class_getDeclaredFields__;
#endif
#ifdef XMLVM_VTABLE_IDX_java_lang_Class_getDeclaredMethods__
    __TIB_java_lang_Class.vtable[XMLVM_VTABLE_IDX_java_lang_Class_getDeclaredMethods__] = 
        (VTABLE_PTR) java_lang_Class_getDeclaredMethods__;
#endif
#ifdef XMLVM_VTABLE_IDX_java_lang_Class_getEnclosingClass__
    __TIB_java_lang_Class.vtable[XMLVM_VTABLE_IDX_java_lang_Class_getEnclosingClass__] = 
        (VTABLE_PTR) java_lang_Class_getEnclosingClass__;
#endif
#ifdef XMLVM_VTABLE_IDX_java_lang_Class_getEnclosingConstructor__
    __TIB_java_lang_Class.vtable[XMLVM_VTABLE_IDX_java_lang_Class_getEnclosingConstructor__] = 
        (VTABLE_PTR) java_lang_Class_getEnclosingConstructor__;
#endif
#ifdef XMLVM_VTABLE_IDX_java_lang_Class_getEnclosingMethod__
    __TIB_java_lang_Class.vtable[XMLVM_VTABLE_IDX_java_lang_Class_getEnclosingMethod__] = 
        (VTABLE_PTR) java_lang_Class_getEnclosingMethod__;
#endif
#ifdef XMLVM_VTABLE_IDX_java_lang_Class_getEnumConstants__
    __TIB_java_lang_Class.vtable[XMLVM_VTABLE_IDX_java_lang_Class_getEnumConstants__] = 
        (VTABLE_PTR) java_lang_Class_getEnumConstants__;
#endif
#ifdef XMLVM_VTABLE_IDX_java_lang_Class_getField___java_lang_String
    __TIB_java_lang_Class.vtable[XMLVM_VTABLE_IDX_java_lang_Class_getField___java_lang_String] = 
        (VTABLE_PTR) java_lang_Class_getField___java_lang_String;
#endif
#ifdef XMLVM_VTABLE_IDX_java_lang_Class_getFields__
    __TIB_java_lang_Class.vtable[XMLVM_VTABLE_IDX_java_lang_Class_getFields__] = 
        (VTABLE_PTR) java_lang_Class_getFields__;
#endif
#ifdef XMLVM_VTABLE_IDX_java_lang_Class_getInterfaces__
    __TIB_java_lang_Class.vtable[XMLVM_VTABLE_IDX_java_lang_Class_getInterfaces__] = 
        (VTABLE_PTR) java_lang_Class_getInterfaces__;
#endif
#ifdef XMLVM_VTABLE_IDX_java_lang_Class_getModifiers__
    __TIB_java_lang_Class.vtable[XMLVM_VTABLE_IDX_java_lang_Class_getModifiers__] = 
        (VTABLE_PTR) java_lang_Class_getModifiers__;
#endif
#ifdef XMLVM_VTABLE_IDX_java_lang_Class_getName__
    __TIB_java_lang_Class.vtable[XMLVM_VTABLE_IDX_java_lang_Class_getName__] = 
        (VTABLE_PTR) java_lang_Class_getName__;
#endif
#ifdef XMLVM_VTABLE_IDX_java_lang_Class_getSimpleName__
    __TIB_java_lang_Class.vtable[XMLVM_VTABLE_IDX_java_lang_Class_getSimpleName__] = 
        (VTABLE_PTR) java_lang_Class_getSimpleName__;
#endif
#ifdef XMLVM_VTABLE_IDX_java_lang_Class_getProtectionDomain__
    __TIB_java_lang_Class.vtable[XMLVM_VTABLE_IDX_java_lang_Class_getProtectionDomain__] = 
        (VTABLE_PTR) java_lang_Class_getProtectionDomain__;
#endif
#ifdef XMLVM_VTABLE_IDX_java_lang_Class_getPDImpl__
    __TIB_java_lang_Class.vtable[XMLVM_VTABLE_IDX_java_lang_Class_getPDImpl__] = 
        (VTABLE_PTR) java_lang_Class_getPDImpl__;
#endif
#ifdef XMLVM_VTABLE_IDX_java_lang_Class_getSigners__
    __TIB_java_lang_Class.vtable[XMLVM_VTABLE_IDX_java_lang_Class_getSigners__] = 
        (VTABLE_PTR) java_lang_Class_getSigners__;
#endif
#ifdef XMLVM_VTABLE_IDX_java_lang_Class_getSuperclass__
    __TIB_java_lang_Class.vtable[XMLVM_VTABLE_IDX_java_lang_Class_getSuperclass__] = 
        (VTABLE_PTR) java_lang_Class_getSuperclass__;
#endif
#ifdef XMLVM_VTABLE_IDX_java_lang_Class_isAnnotation__
    __TIB_java_lang_Class.vtable[XMLVM_VTABLE_IDX_java_lang_Class_isAnnotation__] = 
        (VTABLE_PTR) java_lang_Class_isAnnotation__;
#endif
#ifdef XMLVM_VTABLE_IDX_java_lang_Class_isAnnotationPresent___java_lang_Class
    __TIB_java_lang_Class.vtable[XMLVM_VTABLE_IDX_java_lang_Class_isAnnotationPresent___java_lang_Class] = 
        (VTABLE_PTR) java_lang_Class_isAnnotationPresent___java_lang_Class;
#endif
#ifdef XMLVM_VTABLE_IDX_java_lang_Class_isAnonymousClass__
    __TIB_java_lang_Class.vtable[XMLVM_VTABLE_IDX_java_lang_Class_isAnonymousClass__] = 
        (VTABLE_PTR) java_lang_Class_isAnonymousClass__;
#endif
#ifdef XMLVM_VTABLE_IDX_java_lang_Class_isArray__
    __TIB_java_lang_Class.vtable[XMLVM_VTABLE_IDX_java_lang_Class_isArray__] = 
        (VTABLE_PTR) java_lang_Class_isArray__;
#endif
#ifdef XMLVM_VTABLE_IDX_java_lang_Class_isAssignableFrom___java_lang_Class
    __TIB_java_lang_Class.vtable[XMLVM_VTABLE_IDX_java_lang_Class_isAssignableFrom___java_lang_Class] = 
        (VTABLE_PTR) java_lang_Class_isAssignableFrom___java_lang_Class;
#endif
#ifdef XMLVM_VTABLE_IDX_java_lang_Class_isEnum__
    __TIB_java_lang_Class.vtable[XMLVM_VTABLE_IDX_java_lang_Class_isEnum__] = 
        (VTABLE_PTR) java_lang_Class_isEnum__;
#endif
#ifdef XMLVM_VTABLE_IDX_java_lang_Class_isInstance___java_lang_Object
    __TIB_java_lang_Class.vtable[XMLVM_VTABLE_IDX_java_lang_Class_isInstance___java_lang_Object] = 
        (VTABLE_PTR) java_lang_Class_isInstance___java_lang_Object;
#endif
#ifdef XMLVM_VTABLE_IDX_java_lang_Class_isInterface__
    __TIB_java_lang_Class.vtable[XMLVM_VTABLE_IDX_java_lang_Class_isInterface__] = 
        (VTABLE_PTR) java_lang_Class_isInterface__;
#endif
#ifdef XMLVM_VTABLE_IDX_java_lang_Class_isLocalClass__
    __TIB_java_lang_Class.vtable[XMLVM_VTABLE_IDX_java_lang_Class_isLocalClass__] = 
        (VTABLE_PTR) java_lang_Class_isLocalClass__;
#endif
#ifdef XMLVM_VTABLE_IDX_java_lang_Class_isMemberClass__
    __TIB_java_lang_Class.vtable[XMLVM_VTABLE_IDX_java_lang_Class_isMemberClass__] = 
        (VTABLE_PTR) java_lang_Class_isMemberClass__;
#endif
#ifdef XMLVM_VTABLE_IDX_java_lang_Class_isPrimitive__
    __TIB_java_lang_Class.vtable[XMLVM_VTABLE_IDX_java_lang_Class_isPrimitive__] = 
        (VTABLE_PTR) java_lang_Class_isPrimitive__;
#endif
#ifdef XMLVM_VTABLE_IDX_java_lang_Class_isSynthetic__
    __TIB_java_lang_Class.vtable[XMLVM_VTABLE_IDX_java_lang_Class_isSynthetic__] = 
        (VTABLE_PTR) java_lang_Class_isSynthetic__;
#endif
#ifdef XMLVM_VTABLE_IDX_java_lang_Class_newInstance__
    __TIB_java_lang_Class.vtable[XMLVM_VTABLE_IDX_java_lang_Class_newInstance__] = 
        (VTABLE_PTR) java_lang_Class_newInstance__;
#endif
#ifdef XMLVM_VTABLE_IDX_java_lang_Class_desiredAssertionStatus__
    __TIB_java_lang_Class.vtable[XMLVM_VTABLE_IDX_java_lang_Class_desiredAssertionStatus__] = 
        (VTABLE_PTR) java_lang_Class_desiredAssertionStatus__;
#endif
#ifdef XMLVM_VTABLE_IDX_java_lang_Class_asSubclass___java_lang_Class
    __TIB_java_lang_Class.vtable[XMLVM_VTABLE_IDX_java_lang_Class_asSubclass___java_lang_Class] = 
        (VTABLE_PTR) java_lang_Class_asSubclass___java_lang_Class;
#endif
}