#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int* __val; } ;
typedef  TYPE_1__ sem_t ;

/* Variables and functions */

int sem_getvalue(sem_t *restrict sem, int *restrict valp)
{
	int val = sem->__val[0];
	*valp = val < 0 ? 0 : val;
	return 0;
}