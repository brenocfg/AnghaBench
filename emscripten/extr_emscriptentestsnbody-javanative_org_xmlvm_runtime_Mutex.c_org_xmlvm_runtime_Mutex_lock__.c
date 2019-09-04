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
struct TYPE_4__ {scalar_t__ nativeMutex_; } ;
struct TYPE_5__ {TYPE_1__ org_xmlvm_runtime_Mutex; } ;
struct TYPE_6__ {TYPE_2__ fields; } ;
typedef  TYPE_3__ org_xmlvm_runtime_Mutex ;
typedef  scalar_t__ JAVA_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,int) ; 
 int pthread_mutex_lock (scalar_t__) ; 

void org_xmlvm_runtime_Mutex_lock__(JAVA_OBJECT me)
{
    //XMLVM_BEGIN_NATIVE[org_xmlvm_runtime_Mutex_lock__]
    JAVA_OBJECT m = ((org_xmlvm_runtime_Mutex*) me)->fields.org_xmlvm_runtime_Mutex.nativeMutex_;
    int result = pthread_mutex_lock(m);
    if (result != 0) {
        printf("Error locking mutex! %i\n", result);
    }
    //XMLVM_END_NATIVE
}