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
typedef  int /*<<< orphan*/  thrd_t ;

/* Variables and functions */
 int /*<<< orphan*/  __pthread_join (int /*<<< orphan*/ ,void**) ; 
 int thrd_success ; 

int thrd_join(thrd_t t, int *res)
{
        void *pthread_res;
        __pthread_join(t, &pthread_res);
        if (res) *res = (int)(intptr_t)pthread_res;
        return thrd_success;
}