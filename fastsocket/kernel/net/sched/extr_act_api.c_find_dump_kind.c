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
struct tcamsg {int dummy; } ;
struct nlmsghdr {int dummy; } ;
struct nlattr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NLMSG_ALIGN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TCAA_MAX ; 
 size_t TCA_ACT_KIND ; 
 int /*<<< orphan*/  TCA_ACT_MAX ; 
 int /*<<< orphan*/  TCA_ACT_MAX_PRIO ; 
 size_t TCA_ACT_TAB ; 
 int /*<<< orphan*/  nla_data (struct nlattr*) ; 
 int /*<<< orphan*/  nla_len (struct nlattr*) ; 
 scalar_t__ nla_parse (struct nlattr**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ nlmsg_parse (struct nlmsghdr const*,int,struct nlattr**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct nlattr *
find_dump_kind(const struct nlmsghdr *n)
{
	struct nlattr *tb1, *tb2[TCA_ACT_MAX+1];
	struct nlattr *tb[TCA_ACT_MAX_PRIO + 1];
	struct nlattr *nla[TCAA_MAX + 1];
	struct nlattr *kind;

	if (nlmsg_parse(n, sizeof(struct tcamsg), nla, TCAA_MAX, NULL) < 0)
		return NULL;
	tb1 = nla[TCA_ACT_TAB];
	if (tb1 == NULL)
		return NULL;

	if (nla_parse(tb, TCA_ACT_MAX_PRIO, nla_data(tb1),
		      NLMSG_ALIGN(nla_len(tb1)), NULL) < 0)
		return NULL;

	if (tb[1] == NULL)
		return NULL;
	if (nla_parse(tb2, TCA_ACT_MAX, nla_data(tb[1]),
		      nla_len(tb[1]), NULL) < 0)
		return NULL;
	kind = tb2[TCA_ACT_KIND];

	return kind;
}