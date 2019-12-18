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
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 int proc_importance_assertion_complete (int /*<<< orphan*/ ) ; 

int
proc_denap_assertion_complete(uint64_t assertion_token)
{
	return proc_importance_assertion_complete(assertion_token);
}