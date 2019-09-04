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
struct TYPE_4__ {scalar_t__ parameterTypes_; } ;
struct TYPE_5__ {TYPE_1__ java_lang_reflect_Constructor; } ;
struct TYPE_6__ {TYPE_2__ fields; } ;
typedef  TYPE_3__ java_lang_reflect_Constructor ;
typedef  scalar_t__ JAVA_OBJECT ;

/* Variables and functions */

JAVA_OBJECT java_lang_reflect_Constructor_getParameterTypes__(JAVA_OBJECT me)
{
    //XMLVM_BEGIN_NATIVE[java_lang_reflect_Constructor_getParameterTypes__]
    java_lang_reflect_Constructor* thiz = (java_lang_reflect_Constructor*) me;
    return thiz->fields.java_lang_reflect_Constructor.parameterTypes_;
    //XMLVM_END_NATIVE
}