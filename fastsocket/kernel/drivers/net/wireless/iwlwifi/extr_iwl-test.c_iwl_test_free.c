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
struct iwl_test {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  iwl_test_mem_stop (struct iwl_test*) ; 
 int /*<<< orphan*/  iwl_test_trace_stop (struct iwl_test*) ; 

void iwl_test_free(struct iwl_test *tst)
{
	iwl_test_mem_stop(tst);
	iwl_test_trace_stop(tst);
}