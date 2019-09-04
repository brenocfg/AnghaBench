#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ tib_; } ;
struct TYPE_10__ {TYPE_1__ java_lang_Class; } ;
struct TYPE_11__ {TYPE_2__ fields; } ;
typedef  TYPE_3__ java_lang_Class ;
struct TYPE_12__ {void* clazz; int /*<<< orphan*/  arrayType; void* baseType; int /*<<< orphan*/  flags; } ;
typedef  TYPE_4__ __TIB_DEFINITION_org_xmlvm_runtime_XMLVMArray ;
struct TYPE_13__ {void* arrayType; } ;
typedef  TYPE_5__ __TIB_DEFINITION_TEMPLATE ;
typedef  void* JAVA_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  JAVA_NULL ; 
 TYPE_4__* XMLVM_MALLOC (int) ; 
 int /*<<< orphan*/  XMLVM_MEMCPY (TYPE_4__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  XMLVM_TYPE_ARRAY ; 
 void* __NEW_java_lang_Class () ; 
 int /*<<< orphan*/  __TIB_org_xmlvm_runtime_XMLVMArray ; 
 int /*<<< orphan*/  java_lang_Class___INIT____java_lang_Object (void*,TYPE_4__*) ; 

JAVA_OBJECT XMLVM_CREATE_ARRAY_CLASS_OBJECT(JAVA_OBJECT baseType)
{
    __TIB_DEFINITION_org_xmlvm_runtime_XMLVMArray* tib = XMLVM_MALLOC(sizeof(__TIB_DEFINITION_org_xmlvm_runtime_XMLVMArray));
    XMLVM_MEMCPY(tib, &__TIB_org_xmlvm_runtime_XMLVMArray, sizeof(__TIB_DEFINITION_org_xmlvm_runtime_XMLVMArray));
    tib->flags = XMLVM_TYPE_ARRAY;
    tib->baseType = baseType;
    tib->arrayType = JAVA_NULL;
    JAVA_OBJECT clazz = __NEW_java_lang_Class();
    java_lang_Class___INIT____java_lang_Object(clazz, tib);
    tib->clazz = clazz;
    // Set the arrayType in in baseType to this newly created array type class
    java_lang_Class* baseTypeClass = (java_lang_Class*) baseType;
    __TIB_DEFINITION_TEMPLATE* baseTypeTIB = (__TIB_DEFINITION_TEMPLATE*) baseTypeClass->fields.java_lang_Class.tib_;
    baseTypeTIB->arrayType = clazz;
    return clazz;
}