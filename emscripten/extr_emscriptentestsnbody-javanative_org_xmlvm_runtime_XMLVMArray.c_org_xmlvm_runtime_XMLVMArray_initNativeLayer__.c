#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ VTABLE_PTR ;
struct TYPE_2__ {scalar_t__* vtable; } ;

/* Variables and functions */
 size_t XMLVM_VTABLE_IDX_java_lang_Object_getClass__ ; 
 TYPE_1__ __TIB_org_xmlvm_runtime_XMLVMArray ; 
 scalar_t__ org_xmlvm_runtime_XMLVMArray_getClass__ ; 

void org_xmlvm_runtime_XMLVMArray_initNativeLayer__()
{
    //XMLVM_BEGIN_NATIVE[org_xmlvm_runtime_XMLVMArray_initNativeLayer__]
    __TIB_org_xmlvm_runtime_XMLVMArray.vtable[XMLVM_VTABLE_IDX_java_lang_Object_getClass__] = 
        (VTABLE_PTR) org_xmlvm_runtime_XMLVMArray_getClass__;
    //XMLVM_END_NATIVE
}