#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  pthread_cond_t ;
typedef  int /*<<< orphan*/  JAVA_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/ * getConditionPtr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int pthread_cond_broadcast (int /*<<< orphan*/ *) ; 

void org_xmlvm_runtime_Condition_broadcast__(JAVA_OBJECT me)
{
    //XMLVM_BEGIN_NATIVE[org_xmlvm_runtime_Condition_broadcast__]
    pthread_cond_t* condPtr = getConditionPtr(me);
    int result = pthread_cond_broadcast(condPtr);
    if (result != 0) {
        printf("ERROR: pthread_cond_broadcast response was %i\n", result);
    }
    //XMLVM_END_NATIVE
}