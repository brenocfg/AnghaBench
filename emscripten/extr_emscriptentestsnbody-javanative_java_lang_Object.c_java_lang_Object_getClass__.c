#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* tib; } ;
typedef  TYPE_2__ java_lang_Object ;
struct TYPE_3__ {scalar_t__ clazz; } ;
typedef  scalar_t__ JAVA_OBJECT ;

/* Variables and functions */

JAVA_OBJECT java_lang_Object_getClass__(JAVA_OBJECT me)
{
    //XMLVM_BEGIN_NATIVE[java_lang_Object_getClass__]
    java_lang_Object* o = (java_lang_Object*) me;
    return o->tib->clazz;
    //XMLVM_END_NATIVE
}