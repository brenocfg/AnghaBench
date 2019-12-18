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
typedef  int /*<<< orphan*/  gregset_t ;

/* Variables and functions */
 int /*<<< orphan*/  amd64_supply_native_gregset (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  current_regcache ; 

void
supply_gregset (gregset_t *gregsetp)
{
  amd64_supply_native_gregset (current_regcache, gregsetp, -1);
}