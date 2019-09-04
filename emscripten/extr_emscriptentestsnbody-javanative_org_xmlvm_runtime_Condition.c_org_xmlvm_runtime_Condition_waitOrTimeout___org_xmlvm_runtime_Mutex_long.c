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
struct timeval {int tv_usec; scalar_t__ tv_sec; } ;
struct timespec {int tv_nsec; scalar_t__ tv_sec; } ;
typedef  int /*<<< orphan*/  pthread_cond_t ;
struct TYPE_4__ {scalar_t__ nativeMutex_; } ;
struct TYPE_5__ {TYPE_1__ org_xmlvm_runtime_Mutex; } ;
struct TYPE_6__ {TYPE_2__ fields; } ;
typedef  TYPE_3__ org_xmlvm_runtime_Mutex ;
typedef  scalar_t__ JAVA_OBJECT ;
typedef  int JAVA_LONG ;
typedef  int JAVA_BOOLEAN ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/ * getConditionPtr (scalar_t__) ; 
 int /*<<< orphan*/  gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int pthread_cond_timedwait (int /*<<< orphan*/ *,scalar_t__,struct timespec*) ; 

JAVA_BOOLEAN org_xmlvm_runtime_Condition_waitOrTimeout___org_xmlvm_runtime_Mutex_long(JAVA_OBJECT me, JAVA_OBJECT n1, JAVA_LONG n2)
{
    //XMLVM_BEGIN_NATIVE[org_xmlvm_runtime_Condition_waitOrTimeout___org_xmlvm_runtime_Mutex_long]
    pthread_cond_t* condPtr = getConditionPtr(me);
    JAVA_OBJECT mutex = ((org_xmlvm_runtime_Mutex*)n1)->fields.org_xmlvm_runtime_Mutex.nativeMutex_;

    struct timeval now;
    gettimeofday(&now, NULL);

    struct timespec to;
    // To avoid an overflow error, we drop precision on microseconds (usec) in favor of milliseconds.
    // The loss of precision at the microsecond level is not of concern.
    JAVA_LONG msec = (now.tv_usec / 1000) + n2;
    to.tv_sec = now.tv_sec + (msec / 1000);
    to.tv_nsec = (msec % 1000) * 1000000;

    int result = pthread_cond_timedwait(condPtr, mutex, &to);
    int timedOut = 0;
    if (result == ETIMEDOUT) {
        timedOut = 1;
    } else if (result != 0) {
        printf("ERROR: pthread_cond_timedwait response was %i\n", result);
    }
    return timedOut;
    //XMLVM_END_NATIVE
}