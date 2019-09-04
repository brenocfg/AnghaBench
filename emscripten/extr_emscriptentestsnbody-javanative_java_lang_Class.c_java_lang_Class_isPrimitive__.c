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
struct TYPE_8__ {int flags; } ;
typedef  TYPE_4__ __TIB_DEFINITION_TEMPLATE ;
typedef  scalar_t__ JAVA_OBJECT ;
typedef  int JAVA_BOOLEAN ;

/* Variables and functions */
 int XMLVM_TYPE_PRIMITIVE ; 

JAVA_BOOLEAN java_lang_Class_isPrimitive__(JAVA_OBJECT me)
{
    //XMLVM_BEGIN_NATIVE[java_lang_Class_isPrimitive__]
    java_lang_Class* thiz = (java_lang_Class*) me;
    __TIB_DEFINITION_TEMPLATE* tib = (__TIB_DEFINITION_TEMPLATE*) thiz->fields.java_lang_Class.tib_;
    return (tib->flags & XMLVM_TYPE_PRIMITIVE) != 0;
    //XMLVM_END_NATIVE
}