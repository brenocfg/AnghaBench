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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  sysset_t ;
struct TYPE_3__ {int num_syscalls; } ;
typedef  TYPE_1__ procinfo ;

/* Variables and functions */

__attribute__((used)) static int
sysset_t_size (procinfo * pi)
{
#ifndef DYNAMIC_SYSCALLS
  return sizeof (sysset_t);
#else
  return sizeof (sysset_t) - sizeof (uint64_t)
    + sizeof (uint64_t) * ((pi->num_syscalls + (8 * sizeof (uint64_t) - 1))
			   / (8 * sizeof (uint64_t)));
#endif
}