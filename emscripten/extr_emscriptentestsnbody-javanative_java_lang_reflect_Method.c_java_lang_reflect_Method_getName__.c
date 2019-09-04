#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_3__* name_; } ;
struct TYPE_8__ {TYPE_1__ java_lang_reflect_Method; } ;
struct TYPE_9__ {TYPE_2__ fields; } ;
typedef  TYPE_3__ java_lang_reflect_Method ;
typedef  TYPE_3__* JAVA_OBJECT ;

/* Variables and functions */

JAVA_OBJECT java_lang_reflect_Method_getName__(JAVA_OBJECT me)
{
    //XMLVM_BEGIN_NATIVE[java_lang_reflect_Method_getName__]
    java_lang_reflect_Method* thiz = me;
    return thiz->fields.java_lang_reflect_Method.name_;
    //XMLVM_END_NATIVE
}