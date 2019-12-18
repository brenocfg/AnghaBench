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
struct nlattr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTA_HELP_MAX ; 
 size_t CTA_HELP_NAME ; 
 int EINVAL ; 
 char* nla_data (struct nlattr*) ; 
 int /*<<< orphan*/  nla_parse_nested (struct nlattr**,int /*<<< orphan*/ ,struct nlattr const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int
ctnetlink_parse_help(const struct nlattr *attr, char **helper_name)
{
	struct nlattr *tb[CTA_HELP_MAX+1];

	nla_parse_nested(tb, CTA_HELP_MAX, attr, NULL);

	if (!tb[CTA_HELP_NAME])
		return -EINVAL;

	*helper_name = nla_data(tb[CTA_HELP_NAME]);

	return 0;
}