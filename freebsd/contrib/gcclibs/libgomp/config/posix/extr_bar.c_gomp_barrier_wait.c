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
typedef  int /*<<< orphan*/  gomp_barrier_t ;

/* Variables and functions */
 int /*<<< orphan*/  gomp_barrier_wait_end (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gomp_barrier_wait_start (int /*<<< orphan*/ *) ; 

void
gomp_barrier_wait (gomp_barrier_t *barrier)
{
  gomp_barrier_wait_end (barrier, gomp_barrier_wait_start (barrier));
}