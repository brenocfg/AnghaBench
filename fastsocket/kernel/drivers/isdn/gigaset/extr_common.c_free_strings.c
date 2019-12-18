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
struct at_state_t {int /*<<< orphan*/ ** str_var; } ;

/* Variables and functions */
 int STR_NUM ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void free_strings(struct at_state_t *at_state)
{
	int i;

	for (i = 0; i < STR_NUM; ++i) {
		kfree(at_state->str_var[i]);
		at_state->str_var[i] = NULL;
	}
}