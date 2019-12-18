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
 int /*<<< orphan*/  gomp_iter_static_next (long*,long*) ; 

__attribute__((used)) static bool
gomp_loop_static_next (long *istart, long *iend)
{
  return !gomp_iter_static_next (istart, iend);
}