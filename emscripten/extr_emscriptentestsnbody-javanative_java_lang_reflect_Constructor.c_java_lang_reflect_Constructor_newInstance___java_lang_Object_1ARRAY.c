#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  address_; } ;
struct TYPE_5__ {TYPE_1__ java_lang_reflect_Constructor; } ;
struct TYPE_6__ {TYPE_2__ fields; } ;
typedef  TYPE_3__ java_lang_reflect_Constructor ;
typedef  scalar_t__ JAVA_OBJECT ;
typedef  scalar_t__ (* Func_OOO ) (scalar_t__,scalar_t__) ;

/* Variables and functions */
 scalar_t__ stub1 (scalar_t__,scalar_t__) ; 

JAVA_OBJECT java_lang_reflect_Constructor_newInstance___java_lang_Object_1ARRAY(JAVA_OBJECT me, JAVA_OBJECT n1)
{
    //XMLVM_BEGIN_NATIVE[java_lang_reflect_Constructor_newInstance___java_lang_Object_1ARRAY]
    java_lang_reflect_Constructor* thiz = (java_lang_reflect_Constructor*) me;
    Func_OOO dispatcher = (Func_OOO) thiz->fields.java_lang_reflect_Constructor.address_;
    return (*dispatcher)(me, n1);
    //XMLVM_END_NATIVE
}