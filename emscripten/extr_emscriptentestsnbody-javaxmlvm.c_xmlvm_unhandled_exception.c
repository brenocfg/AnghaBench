#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  xmlvmException_; } ;
struct TYPE_6__ {TYPE_1__ java_lang_Thread; } ;
struct TYPE_7__ {TYPE_2__ fields; } ;
typedef  TYPE_3__ java_lang_Thread ;
typedef  int /*<<< orphan*/  JAVA_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  java_lang_Class_getName__ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  java_lang_Object_getClass__ (int /*<<< orphan*/ ) ; 
 scalar_t__ java_lang_Thread_currentThread__ () ; 
 int /*<<< orphan*/  java_lang_Thread_getName__ (TYPE_3__*) ; 
 int /*<<< orphan*/  java_lang_Throwable_getMessage__ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*,char*,char*) ; 
 char* xmlvm_java_string_to_const_char (int /*<<< orphan*/ ) ; 

void xmlvm_unhandled_exception()
{
    java_lang_Thread* curThread;
    curThread = (java_lang_Thread*) java_lang_Thread_currentThread__();
    JAVA_OBJECT exception = curThread->fields.java_lang_Thread.xmlvmException_;

    JAVA_OBJECT thread_name;
#ifdef XMLVM_VTABLE_IDX_java_lang_Thread_getName__
    thread_name =  ((Func_OO) ((java_lang_Thread*) curThread)->tib->vtable[XMLVM_VTABLE_IDX_java_lang_Thread_getName__])(curThread);
#else
    thread_name = java_lang_Thread_getName__(curThread);
#endif

#ifdef XMLVM_ENABLE_STACK_TRACES

    printf("Exception in thread \"%s\" ",
            xmlvm_java_string_to_const_char(thread_name));
    java_lang_Throwable_printStackTrace__(exception);

#else

    JAVA_OBJECT message;
#ifdef XMLVM_VTABLE_IDX_java_lang_Throwable_getMessage__
    message = ((Func_OO) ((java_lang_Throwable*) exception)->tib->vtable[XMLVM_VTABLE_IDX_java_lang_Throwable_getMessage__])(exception);
#else
    message = java_lang_Throwable_getMessage__(exception);
#endif

    JAVA_OBJECT exception_class;
#ifdef XMLVM_VTABLE_IDX_java_lang_Object_getClass__
    exception_class = ((Func_OO) ((java_lang_Object*) exception)->tib->vtable[XMLVM_VTABLE_IDX_java_lang_Object_getClass__])(exception);
#else
    exception_class = java_lang_Object_getClass__(exception);
#endif

    JAVA_OBJECT class_name;
#ifdef XMLVM_VTABLE_IDX_java_lang_Class_getName__
    class_name = ((Func_OO) ((java_lang_Class*) exception_class)->tib->vtable[XMLVM_VTABLE_IDX_java_lang_Class_getName__])(exception_class);
#else
    class_name = java_lang_Class_getName__(exception_class);
#endif
    
    printf("Exception in thread \"%s\" %s: %s\n",
            xmlvm_java_string_to_const_char(thread_name),
            xmlvm_java_string_to_const_char(class_name),
            xmlvm_java_string_to_const_char(message));

#endif
}