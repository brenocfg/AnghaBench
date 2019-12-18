#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ip6t_standard_target {unsigned int verdict; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;
struct TYPE_4__ {TYPE_1__ user; } ;
struct ip6t_entry_target {TYPE_2__ u; } ;
struct ip6t_entry {int /*<<< orphan*/  ipv6; } ;

/* Variables and functions */
 unsigned int NF_ACCEPT ; 
 unsigned int NF_DROP ; 
 int /*<<< orphan*/  XT_STANDARD_TARGET ; 
 struct ip6t_entry_target* ip6t_get_target (struct ip6t_entry*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unconditional (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool check_underflow(struct ip6t_entry *e)
{
	const struct ip6t_entry_target *t;
	unsigned int verdict;

	if (!unconditional(&e->ipv6))
		return false;
	t = ip6t_get_target(e);
	if (strcmp(t->u.user.name, XT_STANDARD_TARGET) != 0)
		return false;
	verdict = ((struct ip6t_standard_target *)t)->verdict;
	verdict = -verdict - 1;
	return verdict == NF_DROP || verdict == NF_ACCEPT;
}