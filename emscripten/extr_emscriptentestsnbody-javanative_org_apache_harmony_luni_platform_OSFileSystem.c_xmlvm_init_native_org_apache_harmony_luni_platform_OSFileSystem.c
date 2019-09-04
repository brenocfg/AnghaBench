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

void xmlvm_init_native_org_apache_harmony_luni_platform_OSFileSystem()
{
    //XMLVM_BEGIN_NATIVE_IMPLEMENTATION_INIT
    //XMLVM_END_NATIVE_IMPLEMENTATION_INIT
#ifdef XMLVM_VTABLE_IDX_org_apache_harmony_luni_platform_OSFileSystem_getAllocGranularity__
    __TIB_org_apache_harmony_luni_platform_OSFileSystem.vtable[XMLVM_VTABLE_IDX_org_apache_harmony_luni_platform_OSFileSystem_getAllocGranularity__] = 
        (VTABLE_PTR) org_apache_harmony_luni_platform_OSFileSystem_getAllocGranularity__;
#endif
#ifdef XMLVM_VTABLE_IDX_org_apache_harmony_luni_platform_OSFileSystem_writev___long_java_lang_Object_1ARRAY_int_1ARRAY_int_1ARRAY_int
    __TIB_org_apache_harmony_luni_platform_OSFileSystem.vtable[XMLVM_VTABLE_IDX_org_apache_harmony_luni_platform_OSFileSystem_writev___long_java_lang_Object_1ARRAY_int_1ARRAY_int_1ARRAY_int] = 
        (VTABLE_PTR) org_apache_harmony_luni_platform_OSFileSystem_writev___long_java_lang_Object_1ARRAY_int_1ARRAY_int_1ARRAY_int;
#endif
}