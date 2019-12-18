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
struct timespec {int dummy; } ;
typedef  int /*<<< orphan*/  mtx_t ;

/* Variables and functions */
 int thrd_error ; 

int mtx_timedlock(mtx_t *mtx, const struct timespec *ts)
{
  /* FIXME! */
  (void)mtx;
  (void)ts;
  return thrd_error;
}