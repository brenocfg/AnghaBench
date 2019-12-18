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

/* Variables and functions */
 int /*<<< orphan*/  pthread_exit (void*) ; 

__attribute__((used)) static void *compute_square(void *arg)
{
    int *num = (int *) arg;
    *num = (*num) * (*num);
    pthread_exit((void *) num);
    return NULL;
}