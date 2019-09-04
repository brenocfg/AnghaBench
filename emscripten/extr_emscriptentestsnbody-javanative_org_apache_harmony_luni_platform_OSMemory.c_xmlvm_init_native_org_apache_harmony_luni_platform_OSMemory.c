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

void xmlvm_init_native_org_apache_harmony_luni_platform_OSMemory()
{
    //XMLVM_BEGIN_NATIVE_IMPLEMENTATION_INIT
    //XMLVM_END_NATIVE_IMPLEMENTATION_INIT
#ifdef XMLVM_VTABLE_IDX_org_apache_harmony_luni_platform_OSMemory_malloc___long
    __TIB_org_apache_harmony_luni_platform_OSMemory.vtable[XMLVM_VTABLE_IDX_org_apache_harmony_luni_platform_OSMemory_malloc___long] = 
        (VTABLE_PTR) org_apache_harmony_luni_platform_OSMemory_malloc___long;
#endif
#ifdef XMLVM_VTABLE_IDX_org_apache_harmony_luni_platform_OSMemory_free___long
    __TIB_org_apache_harmony_luni_platform_OSMemory.vtable[XMLVM_VTABLE_IDX_org_apache_harmony_luni_platform_OSMemory_free___long] = 
        (VTABLE_PTR) org_apache_harmony_luni_platform_OSMemory_free___long;
#endif
#ifdef XMLVM_VTABLE_IDX_org_apache_harmony_luni_platform_OSMemory_memset___long_byte_long
    __TIB_org_apache_harmony_luni_platform_OSMemory.vtable[XMLVM_VTABLE_IDX_org_apache_harmony_luni_platform_OSMemory_memset___long_byte_long] = 
        (VTABLE_PTR) org_apache_harmony_luni_platform_OSMemory_memset___long_byte_long;
#endif
#ifdef XMLVM_VTABLE_IDX_org_apache_harmony_luni_platform_OSMemory_memmove___long_long_long
    __TIB_org_apache_harmony_luni_platform_OSMemory.vtable[XMLVM_VTABLE_IDX_org_apache_harmony_luni_platform_OSMemory_memmove___long_long_long] = 
        (VTABLE_PTR) org_apache_harmony_luni_platform_OSMemory_memmove___long_long_long;
#endif
#ifdef XMLVM_VTABLE_IDX_org_apache_harmony_luni_platform_OSMemory_getByteArray___long_byte_1ARRAY_int_int
    __TIB_org_apache_harmony_luni_platform_OSMemory.vtable[XMLVM_VTABLE_IDX_org_apache_harmony_luni_platform_OSMemory_getByteArray___long_byte_1ARRAY_int_int] = 
        (VTABLE_PTR) org_apache_harmony_luni_platform_OSMemory_getByteArray___long_byte_1ARRAY_int_int;
#endif
#ifdef XMLVM_VTABLE_IDX_org_apache_harmony_luni_platform_OSMemory_setByteArray___long_byte_1ARRAY_int_int
    __TIB_org_apache_harmony_luni_platform_OSMemory.vtable[XMLVM_VTABLE_IDX_org_apache_harmony_luni_platform_OSMemory_setByteArray___long_byte_1ARRAY_int_int] = 
        (VTABLE_PTR) org_apache_harmony_luni_platform_OSMemory_setByteArray___long_byte_1ARRAY_int_int;
#endif
#ifdef XMLVM_VTABLE_IDX_org_apache_harmony_luni_platform_OSMemory_getByte___long
    __TIB_org_apache_harmony_luni_platform_OSMemory.vtable[XMLVM_VTABLE_IDX_org_apache_harmony_luni_platform_OSMemory_getByte___long] = 
        (VTABLE_PTR) org_apache_harmony_luni_platform_OSMemory_getByte___long;
#endif
#ifdef XMLVM_VTABLE_IDX_org_apache_harmony_luni_platform_OSMemory_setByte___long_byte
    __TIB_org_apache_harmony_luni_platform_OSMemory.vtable[XMLVM_VTABLE_IDX_org_apache_harmony_luni_platform_OSMemory_setByte___long_byte] = 
        (VTABLE_PTR) org_apache_harmony_luni_platform_OSMemory_setByte___long_byte;
#endif
#ifdef XMLVM_VTABLE_IDX_org_apache_harmony_luni_platform_OSMemory_getShort___long
    __TIB_org_apache_harmony_luni_platform_OSMemory.vtable[XMLVM_VTABLE_IDX_org_apache_harmony_luni_platform_OSMemory_getShort___long] = 
        (VTABLE_PTR) org_apache_harmony_luni_platform_OSMemory_getShort___long;
#endif
#ifdef XMLVM_VTABLE_IDX_org_apache_harmony_luni_platform_OSMemory_setShort___long_short
    __TIB_org_apache_harmony_luni_platform_OSMemory.vtable[XMLVM_VTABLE_IDX_org_apache_harmony_luni_platform_OSMemory_setShort___long_short] = 
        (VTABLE_PTR) org_apache_harmony_luni_platform_OSMemory_setShort___long_short;
#endif
#ifdef XMLVM_VTABLE_IDX_org_apache_harmony_luni_platform_OSMemory_getInt___long
    __TIB_org_apache_harmony_luni_platform_OSMemory.vtable[XMLVM_VTABLE_IDX_org_apache_harmony_luni_platform_OSMemory_getInt___long] = 
        (VTABLE_PTR) org_apache_harmony_luni_platform_OSMemory_getInt___long;
#endif
#ifdef XMLVM_VTABLE_IDX_org_apache_harmony_luni_platform_OSMemory_setInt___long_int
    __TIB_org_apache_harmony_luni_platform_OSMemory.vtable[XMLVM_VTABLE_IDX_org_apache_harmony_luni_platform_OSMemory_setInt___long_int] = 
        (VTABLE_PTR) org_apache_harmony_luni_platform_OSMemory_setInt___long_int;
#endif
#ifdef XMLVM_VTABLE_IDX_org_apache_harmony_luni_platform_OSMemory_getLong___long
    __TIB_org_apache_harmony_luni_platform_OSMemory.vtable[XMLVM_VTABLE_IDX_org_apache_harmony_luni_platform_OSMemory_getLong___long] = 
        (VTABLE_PTR) org_apache_harmony_luni_platform_OSMemory_getLong___long;
#endif
#ifdef XMLVM_VTABLE_IDX_org_apache_harmony_luni_platform_OSMemory_setLong___long_long
    __TIB_org_apache_harmony_luni_platform_OSMemory.vtable[XMLVM_VTABLE_IDX_org_apache_harmony_luni_platform_OSMemory_setLong___long_long] = 
        (VTABLE_PTR) org_apache_harmony_luni_platform_OSMemory_setLong___long_long;
#endif
#ifdef XMLVM_VTABLE_IDX_org_apache_harmony_luni_platform_OSMemory_getFloat___long
    __TIB_org_apache_harmony_luni_platform_OSMemory.vtable[XMLVM_VTABLE_IDX_org_apache_harmony_luni_platform_OSMemory_getFloat___long] = 
        (VTABLE_PTR) org_apache_harmony_luni_platform_OSMemory_getFloat___long;
#endif
#ifdef XMLVM_VTABLE_IDX_org_apache_harmony_luni_platform_OSMemory_setFloat___long_float
    __TIB_org_apache_harmony_luni_platform_OSMemory.vtable[XMLVM_VTABLE_IDX_org_apache_harmony_luni_platform_OSMemory_setFloat___long_float] = 
        (VTABLE_PTR) org_apache_harmony_luni_platform_OSMemory_setFloat___long_float;
#endif
#ifdef XMLVM_VTABLE_IDX_org_apache_harmony_luni_platform_OSMemory_getDouble___long
    __TIB_org_apache_harmony_luni_platform_OSMemory.vtable[XMLVM_VTABLE_IDX_org_apache_harmony_luni_platform_OSMemory_getDouble___long] = 
        (VTABLE_PTR) org_apache_harmony_luni_platform_OSMemory_getDouble___long;
#endif
#ifdef XMLVM_VTABLE_IDX_org_apache_harmony_luni_platform_OSMemory_setDouble___long_double
    __TIB_org_apache_harmony_luni_platform_OSMemory.vtable[XMLVM_VTABLE_IDX_org_apache_harmony_luni_platform_OSMemory_setDouble___long_double] = 
        (VTABLE_PTR) org_apache_harmony_luni_platform_OSMemory_setDouble___long_double;
#endif
#ifdef XMLVM_VTABLE_IDX_org_apache_harmony_luni_platform_OSMemory_getAddress___long
    __TIB_org_apache_harmony_luni_platform_OSMemory.vtable[XMLVM_VTABLE_IDX_org_apache_harmony_luni_platform_OSMemory_getAddress___long] = 
        (VTABLE_PTR) org_apache_harmony_luni_platform_OSMemory_getAddress___long;
#endif
#ifdef XMLVM_VTABLE_IDX_org_apache_harmony_luni_platform_OSMemory_setAddress___long_long
    __TIB_org_apache_harmony_luni_platform_OSMemory.vtable[XMLVM_VTABLE_IDX_org_apache_harmony_luni_platform_OSMemory_setAddress___long_long] = 
        (VTABLE_PTR) org_apache_harmony_luni_platform_OSMemory_setAddress___long_long;
#endif
}