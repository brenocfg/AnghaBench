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
struct vc_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  con_is_bound (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  newport_con ; 
 int /*<<< orphan*/  newport_exit () ; 
 scalar_t__ newport_has_init ; 

__attribute__((used)) static void newport_deinit(struct vc_data *c)
{
	if (!con_is_bound(&newport_con) && newport_has_init) {
		newport_exit();
		newport_has_init = 0;
	}
}