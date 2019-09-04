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
struct TYPE_4__ {scalar_t__ ptBuffers_; } ;
struct TYPE_5__ {TYPE_1__ java_lang_Thread; } ;
struct TYPE_6__ {TYPE_2__ fields; } ;
typedef  TYPE_3__ java_lang_Thread ;
typedef  int /*<<< orphan*/  PortlibPTBuffers_struct ;

/* Variables and functions */
 scalar_t__ JAVA_NULL ; 
 int /*<<< orphan*/  XMLVM_BZERO (scalar_t__,int) ; 
 scalar_t__ XMLVM_MALLOC (int) ; 
 scalar_t__ java_lang_Thread_currentThread__ () ; 

void* hyport_tls_get ()
{
    java_lang_Thread* curThread = (java_lang_Thread*) java_lang_Thread_currentThread__();
    if (curThread->fields.java_lang_Thread.ptBuffers_ == JAVA_NULL) {
        curThread->fields.java_lang_Thread.ptBuffers_ = XMLVM_MALLOC(sizeof(PortlibPTBuffers_struct));
        XMLVM_BZERO(curThread->fields.java_lang_Thread.ptBuffers_, sizeof(PortlibPTBuffers_struct));
    }
    
    return curThread->fields.java_lang_Thread.ptBuffers_;
}