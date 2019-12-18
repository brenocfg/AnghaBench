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
typedef  int diva_os_atomic_t ;

/* Variables and functions */

__attribute__((used)) static diva_os_atomic_t __inline__
diva_os_atomic_decrement(diva_os_atomic_t* pv)
{
  *pv -= 1;
  return (*pv);
}