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
 int memcmp (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  nla_data (struct nlattr const*) ; 
 int nla_len (struct nlattr const*) ; 
 int strlen (char const*) ; 

int nla_strcmp(const struct nlattr *nla, const char *str)
{
	int len = strlen(str) + 1;
	int d = nla_len(nla) - len;

	if (d == 0)
		d = memcmp(nla_data(nla), str, len);

	return d;
}