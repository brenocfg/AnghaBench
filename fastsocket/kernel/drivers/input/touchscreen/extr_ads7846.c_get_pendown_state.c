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
struct ads7846 {int (* get_pendown_state ) () ;int /*<<< orphan*/  gpio_pendown; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpio_get_value (int /*<<< orphan*/ ) ; 
 int stub1 () ; 

__attribute__((used)) static int get_pendown_state(struct ads7846 *ts)
{
	if (ts->get_pendown_state)
		return ts->get_pendown_state();

	return !gpio_get_value(ts->gpio_pendown);
}