#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ tib_; } ;
struct TYPE_6__ {TYPE_1__ java_lang_Class; } ;
struct TYPE_7__ {TYPE_2__ fields; } ;
typedef  TYPE_3__ java_lang_Class ;
struct TYPE_8__ {int flags; scalar_t__ baseType; } ;
typedef  TYPE_4__ __TIB_DEFINITION_TEMPLATE ;
typedef  scalar_t__ JAVA_OBJECT ;

/* Variables and functions */
 scalar_t__ JAVA_NULL ; 
 int XMLVM_TYPE_ARRAY ; 

JAVA_OBJECT java_lang_Class_getComponentType__(JAVA_OBJECT me)
{
    //XMLVM_BEGIN_NATIVE[java_lang_Class_getComponentType__]
    java_lang_Class* thiz = (java_lang_Class*) me;
    __TIB_DEFINITION_TEMPLATE* tib = (__TIB_DEFINITION_TEMPLATE*) thiz->fields.java_lang_Class.tib_;
    if ((tib->flags & XMLVM_TYPE_ARRAY) == 0) {
        // This is not an array
        return JAVA_NULL;
    }
    return tib->baseType;
    //XMLVM_END_NATIVE
}