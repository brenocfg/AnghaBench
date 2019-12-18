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
struct cpumask {int dummy; } ;

/* Variables and functions */
 int E2BIG ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int TASKSTATS_CPUMASK_MAXLEN ; 
 int cpulist_parse (char*,struct cpumask*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (int,int /*<<< orphan*/ ) ; 
 int nla_len (struct nlattr*) ; 
 int /*<<< orphan*/  nla_strlcpy (char*,struct nlattr*,int) ; 

__attribute__((used)) static int parse(struct nlattr *na, struct cpumask *mask)
{
	char *data;
	int len;
	int ret;

	if (na == NULL)
		return 1;
	len = nla_len(na);
	if (len > TASKSTATS_CPUMASK_MAXLEN)
		return -E2BIG;
	if (len < 1)
		return -EINVAL;
	data = kmalloc(len, GFP_KERNEL);
	if (!data)
		return -ENOMEM;
	nla_strlcpy(data, na, len);
	ret = cpulist_parse(data, mask);
	kfree(data);
	return ret;
}