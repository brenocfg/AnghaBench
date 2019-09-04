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
struct TYPE_4__ {int /*<<< orphan*/  xmlvmExceptionEnv_; } ;
struct TYPE_5__ {TYPE_1__ java_lang_Thread; } ;
struct TYPE_6__ {TYPE_2__ fields; } ;
typedef  TYPE_3__ java_lang_Thread ;
typedef  scalar_t__ JAVA_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  xmlvm_exception_env_main_thread ; 

void java_lang_Thread_initMainThread__(JAVA_OBJECT me)
{
    //XMLVM_BEGIN_NATIVE[java_lang_Thread_initMainThread__]
    ((java_lang_Thread*)me)->fields.java_lang_Thread.xmlvmExceptionEnv_ = xmlvm_exception_env_main_thread;
    //XMLVM_END_NATIVE
}