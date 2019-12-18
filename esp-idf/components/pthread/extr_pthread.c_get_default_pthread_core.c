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
 int CONFIG_PTHREAD_TASK_CORE_DEFAULT ; 
 int tskNO_AFFINITY ; 

__attribute__((used)) static int get_default_pthread_core(void)
{
    return CONFIG_PTHREAD_TASK_CORE_DEFAULT == -1 ? tskNO_AFFINITY : CONFIG_PTHREAD_TASK_CORE_DEFAULT;
}