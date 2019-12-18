#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pf_ruleset {TYPE_3__* rules; } ;
struct TYPE_5__ {scalar_t__ ticket; } ;
struct TYPE_4__ {scalar_t__ ticket; int /*<<< orphan*/  ptr; } ;
struct TYPE_6__ {TYPE_2__ inactive; TYPE_1__ active; } ;

/* Variables and functions */
 int /*<<< orphan*/  pf_calc_skip_steps (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pf_ruleset_cleanup(struct pf_ruleset *ruleset, int rs)
{
	pf_calc_skip_steps(ruleset->rules[rs].active.ptr);
	ruleset->rules[rs].active.ticket =
	    ++ruleset->rules[rs].inactive.ticket;
}