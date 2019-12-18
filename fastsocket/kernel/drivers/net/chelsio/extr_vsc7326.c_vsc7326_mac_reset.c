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
typedef  int /*<<< orphan*/  adapter_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  run_bist_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  run_table (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vsc7326_full_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vsc7326_reset ; 

__attribute__((used)) static int vsc7326_mac_reset(adapter_t *adapter)
{
	vsc7326_full_reset(adapter);
	(void) run_bist_all(adapter);
	run_table(adapter, vsc7326_reset, ARRAY_SIZE(vsc7326_reset));
	return 0;
}