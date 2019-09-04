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
struct TYPE_4__ {scalar_t__ tib_; } ;
struct TYPE_5__ {TYPE_1__ java_lang_Class; } ;
struct TYPE_6__ {TYPE_2__ fields; } ;
typedef  TYPE_3__ java_lang_Class ;
typedef  int /*<<< orphan*/  __TIB_DEFINITION_TEMPLATE ;
typedef  scalar_t__ JAVA_OBJECT ;
typedef  int /*<<< orphan*/  JAVA_BOOLEAN ;

/* Variables and functions */

JAVA_BOOLEAN java_lang_Class_isLocalClass__(JAVA_OBJECT me)
{
    //XMLVM_BEGIN_NATIVE[java_lang_Class_isLocalClass__]
    java_lang_Class* thiz = (java_lang_Class*) me;
    __TIB_DEFINITION_TEMPLATE* tib = (__TIB_DEFINITION_TEMPLATE*) thiz->fields.java_lang_Class.tib_;
    //TODO correct check for local
    return 0;
    //XMLVM_END_NATIVE
}