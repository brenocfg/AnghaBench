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
struct as_io_context {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  AS_TASK_RUNNING ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void exit_as_io_context(struct as_io_context *aic)
{
	WARN_ON(!test_bit(AS_TASK_RUNNING, &aic->state));
	clear_bit(AS_TASK_RUNNING, &aic->state);
}