#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {TYPE_6__* clazz_; } ;
struct TYPE_18__ {TYPE_1__ java_lang_reflect_Method; } ;
struct TYPE_21__ {TYPE_2__ fields; } ;
typedef  TYPE_5__ java_lang_reflect_Method ;
struct TYPE_19__ {TYPE_7__* tib_; } ;
struct TYPE_20__ {TYPE_3__ java_lang_Class; } ;
struct TYPE_22__ {TYPE_4__ fields; } ;
typedef  TYPE_6__ java_lang_Class ;
struct TYPE_23__ {TYPE_5__* (* methodDispatcherFunc ) (TYPE_5__*,TYPE_5__*,TYPE_5__*) ;} ;
typedef  TYPE_7__ __TIB_DEFINITION_TEMPLATE ;
typedef  TYPE_5__* JAVA_OBJECT ;
typedef  TYPE_5__* (* Func_OOOO ) (TYPE_5__*,TYPE_5__*,TYPE_5__*) ;

/* Variables and functions */

JAVA_OBJECT java_lang_reflect_Method_invoke___java_lang_Object_java_lang_Object_1ARRAY(JAVA_OBJECT me, JAVA_OBJECT n1, JAVA_OBJECT n2)
{
    //XMLVM_BEGIN_NATIVE[java_lang_reflect_Method_invoke___java_lang_Object_java_lang_Object_1ARRAY]
    java_lang_reflect_Method* thiz = me;
    java_lang_Class* declaringClass = thiz->fields.java_lang_reflect_Method.clazz_;
    __TIB_DEFINITION_TEMPLATE* tib = declaringClass->fields.java_lang_Class.tib_;
    Func_OOOO dispatcher = tib->methodDispatcherFunc;
    return dispatcher(me, n1, n2);
    //XMLVM_END_NATIVE
}