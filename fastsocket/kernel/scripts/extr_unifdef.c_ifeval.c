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
typedef  int Linetype ;

/* Variables and functions */
 int LT_IF ; 
 int /*<<< orphan*/  debug (char*,...) ; 
 int /*<<< orphan*/  eval_ops ; 
 int eval_table (int /*<<< orphan*/ ,int*,char const**) ; 
 int keepthis ; 
 scalar_t__ killconsts ; 

__attribute__((used)) static Linetype
ifeval(const char **cpp)
{
	const char *cp = *cpp;
	int ret;
	int val;

	debug("eval %s", *cpp);
	keepthis = killconsts ? false : true;
	ret = eval_table(eval_ops, &val, &cp);
	if (ret != LT_IF)
		*cpp = cp;
	debug("eval = %d", val);
	return (keepthis ? LT_IF : ret);
}