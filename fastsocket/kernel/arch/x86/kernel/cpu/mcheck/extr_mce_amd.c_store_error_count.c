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
struct threshold_block {int /*<<< orphan*/  cpu; } ;
struct thresh_restart {int reset; int /*<<< orphan*/  old_limit; struct threshold_block* b; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  smp_call_function_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct thresh_restart*,int) ; 
 int /*<<< orphan*/  threshold_restart_bank ; 

__attribute__((used)) static ssize_t store_error_count(struct threshold_block *b,
				 const char *buf, size_t count)
{
	struct thresh_restart tr = { .b = b, .reset = 1, .old_limit = 0 };

	smp_call_function_single(b->cpu, threshold_restart_bank, &tr, 1);
	return 1;
}