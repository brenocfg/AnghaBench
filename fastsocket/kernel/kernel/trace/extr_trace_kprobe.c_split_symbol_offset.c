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

/* Variables and functions */
 int EINVAL ; 
 char* strchr (char*,char) ; 
 int strict_strtoul (char*,int /*<<< orphan*/ ,unsigned long*) ; 

__attribute__((used)) static int split_symbol_offset(char *symbol, unsigned long *offset)
{
	char *tmp;
	int ret;

	if (!offset)
		return -EINVAL;

	tmp = strchr(symbol, '+');
	if (tmp) {
		/* skip sign because strict_strtol doesn't accept '+' */
		ret = strict_strtoul(tmp + 1, 0, offset);
		if (ret)
			return ret;
		*tmp = '\0';
	} else
		*offset = 0;
	return 0;
}