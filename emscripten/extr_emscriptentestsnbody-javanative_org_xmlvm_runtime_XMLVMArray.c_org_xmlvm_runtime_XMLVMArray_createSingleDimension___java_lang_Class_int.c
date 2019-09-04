#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int sizeOfBaseType; scalar_t__ useAtomicMalloc; } ;
typedef  TYPE_1__ TYPE_INFO ;
typedef  int /*<<< orphan*/  JAVA_OBJECT ;
typedef  int JAVA_INT ;

/* Variables and functions */
 TYPE_1__ XMLVMArray_getTypeInfo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XMLVM_ATOMIC_MALLOC (int) ; 
 int /*<<< orphan*/  XMLVM_BZERO (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  XMLVM_MALLOC (int) ; 
 int /*<<< orphan*/  org_xmlvm_runtime_XMLVMArray_createSingleDimensionWithData___java_lang_Class_int_java_lang_Object (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

JAVA_OBJECT org_xmlvm_runtime_XMLVMArray_createSingleDimension___java_lang_Class_int(JAVA_OBJECT n1, JAVA_INT n2)
{
    //XMLVM_BEGIN_NATIVE[org_xmlvm_runtime_XMLVMArray_createSingleDimension___java_lang_Class_int]
    JAVA_OBJECT type = n1;
    JAVA_INT size = n2;
    TYPE_INFO info = XMLVMArray_getTypeInfo(type);
    int mem_size = info.sizeOfBaseType * size;
    JAVA_OBJECT data = info.useAtomicMalloc ? XMLVM_ATOMIC_MALLOC(mem_size) : XMLVM_MALLOC(mem_size);
    XMLVM_BZERO(data, mem_size);
    return org_xmlvm_runtime_XMLVMArray_createSingleDimensionWithData___java_lang_Class_int_java_lang_Object(type, size, data);
    //XMLVM_END_NATIVE
}