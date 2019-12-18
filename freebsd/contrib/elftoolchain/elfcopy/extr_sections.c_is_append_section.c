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
struct sec_action {scalar_t__ append; int /*<<< orphan*/ * string; } ;
struct elfcopy {int dummy; } ;

/* Variables and functions */
 struct sec_action* lookup_sec_act (struct elfcopy*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
is_append_section(struct elfcopy *ecp, const char *name)
{
	struct sec_action *sac;

	sac = lookup_sec_act(ecp, name, 0);
	if (sac != NULL && sac->append != 0 && sac->string != NULL)
		return (1);

	return (0);
}