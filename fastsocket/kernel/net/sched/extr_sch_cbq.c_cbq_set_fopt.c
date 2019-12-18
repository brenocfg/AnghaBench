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
struct tc_cbq_fopt {int /*<<< orphan*/  defchange; int /*<<< orphan*/  defmap; int /*<<< orphan*/  split; } ;
struct cbq_class {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cbq_change_defmap (struct cbq_class*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cbq_set_fopt(struct cbq_class *cl, struct tc_cbq_fopt *fopt)
{
	cbq_change_defmap(cl, fopt->split, fopt->defmap, fopt->defchange);
	return 0;
}