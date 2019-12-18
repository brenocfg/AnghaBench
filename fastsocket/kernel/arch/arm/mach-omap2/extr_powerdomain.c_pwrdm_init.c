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
struct powerdomain {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _pwrdm_setup (struct powerdomain*) ; 
 int /*<<< orphan*/  pwrdm_register (struct powerdomain*) ; 

void pwrdm_init(struct powerdomain **pwrdm_list)
{
	struct powerdomain **p = NULL;

	if (pwrdm_list) {
		for (p = pwrdm_list; *p; p++) {
			pwrdm_register(*p);
			_pwrdm_setup(*p);
		}
	}
}