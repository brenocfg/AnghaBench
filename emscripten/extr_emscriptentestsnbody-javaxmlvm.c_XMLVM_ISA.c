#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {TYPE_7__* type_; } ;
struct TYPE_15__ {TYPE_1__ org_xmlvm_runtime_XMLVMArray; } ;
struct TYPE_18__ {TYPE_2__ fields; } ;
typedef  TYPE_5__ org_xmlvm_runtime_XMLVMArray ;
struct TYPE_19__ {scalar_t__ tib; } ;
typedef  TYPE_6__ java_lang_Object ;
struct TYPE_16__ {TYPE_8__* tib_; } ;
struct TYPE_17__ {TYPE_3__ java_lang_Class; } ;
struct TYPE_20__ {TYPE_4__ fields; } ;
typedef  TYPE_7__ java_lang_Class ;
struct TYPE_21__ {int numImplementedInterfaces; struct TYPE_21__* extends; struct TYPE_21__*** implementedInterfaces; struct TYPE_21__* baseType; } ;
typedef  TYPE_8__ __TIB_DEFINITION_TEMPLATE ;
typedef  TYPE_8__* JAVA_OBJECT ;

/* Variables and functions */
 TYPE_8__* JAVA_NULL ; 
 TYPE_8__ __TIB_org_xmlvm_runtime_XMLVMArray ; 

int XMLVM_ISA(JAVA_OBJECT obj, JAVA_OBJECT clazz)
{
    if (obj == JAVA_NULL) {
        return 0;
    }
    
    int dimension_tib1 = 0;
    int dimension_tib2 = 0;
    __TIB_DEFINITION_TEMPLATE* tib1 = (__TIB_DEFINITION_TEMPLATE*) ((java_lang_Object*) obj)->tib;
    __TIB_DEFINITION_TEMPLATE* tib2 = (__TIB_DEFINITION_TEMPLATE*) ((java_lang_Class*) clazz)->fields.java_lang_Class.tib_;
    
    if (tib1 == &__TIB_org_xmlvm_runtime_XMLVMArray) {
        java_lang_Class* clazz = ((org_xmlvm_runtime_XMLVMArray*) obj)->fields.org_xmlvm_runtime_XMLVMArray.type_;
        tib1 = clazz->fields.java_lang_Class.tib_;
    }
    
    while (tib1->baseType != JAVA_NULL) {
        tib1 = ((java_lang_Class*) tib1->baseType)->fields.java_lang_Class.tib_;
        dimension_tib1++;
    }
    
    while (tib2->baseType != JAVA_NULL) {
        tib2 = ((java_lang_Class*) tib2->baseType)->fields.java_lang_Class.tib_;
        dimension_tib2++;
    }
    
    if (dimension_tib1 < dimension_tib2) {
        return 0;
    }
    
    while (tib1 != JAVA_NULL) {
        if (tib1 == tib2) {
            return 1;
        }
        // Check all implemented interfaces
        int i;
        for (i = 0; i < tib1->numImplementedInterfaces; i++) {
            if (tib1->implementedInterfaces[0][i] == tib2) {
                return 1;
            }
        }
        tib1 = tib1->extends;
    }
    return 0;
}