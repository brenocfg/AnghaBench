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
typedef  int /*<<< orphan*/  pthread_cond_t ;
struct TYPE_4__ {scalar_t__ nativeMutex_; } ;
struct TYPE_5__ {TYPE_1__ org_xmlvm_runtime_Mutex; } ;
struct TYPE_6__ {TYPE_2__ fields; } ;
typedef  TYPE_3__ org_xmlvm_runtime_Mutex ;
typedef  scalar_t__ JAVA_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/ * getConditionPtr (scalar_t__) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int pthread_cond_wait (int /*<<< orphan*/ *,scalar_t__) ; 

void org_xmlvm_runtime_Condition_wait___org_xmlvm_runtime_Mutex(JAVA_OBJECT me, JAVA_OBJECT n1)
{
    //XMLVM_BEGIN_NATIVE[org_xmlvm_runtime_Condition_wait___org_xmlvm_runtime_Mutex]
    pthread_cond_t* condPtr = getConditionPtr(me);
    JAVA_OBJECT mutex = ((org_xmlvm_runtime_Mutex*)n1)->fields.org_xmlvm_runtime_Mutex.nativeMutex_;
    int result = pthread_cond_wait(condPtr, mutex);
    if (result != 0) {
        printf("ERROR: pthread_cond_wait response was %i\n", result);
    }
    //XMLVM_END_NATIVE
}