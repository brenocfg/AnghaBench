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
typedef  int /*<<< orphan*/  org_xmlvm_runtime_Condition ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * getConditionPtr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_cond_destroy (int /*<<< orphan*/ *) ; 

void nativeConditionCleanup(void* me, void* client_data)
{
    pthread_cond_t* condPtr = getConditionPtr((org_xmlvm_runtime_Condition*)me);
    pthread_cond_destroy(condPtr);
    free(condPtr);
}