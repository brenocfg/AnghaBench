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
typedef  TYPE_1__* pthread_t ;
typedef  int clockid_t ;
struct TYPE_3__ {int tid; } ;

/* Variables and functions */

int pthread_getcpuclockid(pthread_t t, clockid_t *clockid)
{
	*clockid = (-t->tid-1)*8U + 6;
	return 0;
}