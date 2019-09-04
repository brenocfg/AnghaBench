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
typedef  int /*<<< orphan*/  pthread_mutex_t ;
struct TYPE_4__ {int /*<<< orphan*/ * nativeMutex_; } ;
struct TYPE_5__ {TYPE_1__ org_xmlvm_runtime_Mutex; } ;
struct TYPE_6__ {TYPE_2__ fields; } ;
typedef  TYPE_3__ org_xmlvm_runtime_Mutex ;
typedef  scalar_t__ JAVA_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  XMLVM_FINALIZE (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int /*<<< orphan*/  nativeCleanup ; 
 int /*<<< orphan*/  pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void org_xmlvm_runtime_Mutex_initNativeInstance__(JAVA_OBJECT me)
{
    //XMLVM_BEGIN_NATIVE[org_xmlvm_runtime_Mutex_initNativeInstance__]
    pthread_mutex_t* m = malloc(sizeof(pthread_mutex_t));
    pthread_mutex_init(m, NULL);
    ((org_xmlvm_runtime_Mutex*) me)->fields.org_xmlvm_runtime_Mutex.nativeMutex_ = m;
    // Register a finalizer for native cleanup
    XMLVM_FINALIZE(me, nativeCleanup);
    //XMLVM_END_NATIVE
}