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
struct TYPE_3__ {unsigned int total; int /*<<< orphan*/  mutex1; } ;
typedef  TYPE_1__ gomp_barrier_t ;

/* Variables and functions */
 int /*<<< orphan*/  gomp_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gomp_mutex_unlock (int /*<<< orphan*/ *) ; 

void
gomp_barrier_reinit (gomp_barrier_t *bar, unsigned count)
{
  gomp_mutex_lock (&bar->mutex1);
  bar->total = count;
  gomp_mutex_unlock (&bar->mutex1);
}