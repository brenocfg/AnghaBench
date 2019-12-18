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
struct salinfo_data {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  ia64_sal_clear_state_info (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
salinfo_log_clear_cpu(void *context)
{
	struct salinfo_data *data = context;
	ia64_sal_clear_state_info(data->type);
}