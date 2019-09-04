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

int canMatch(char *input, char *rule)
{
	// 返回最长匹配长度 -1表示不匹配
	if (*rule == 0)
	{
		//已经到rule尾端
		return 0;
	}
	int r = -1 , may;
	if (*rule == '*')
	{
		r = canMatch(input, rule + 1);  // *匹配0个字符
		if (*input)
		{
			may = canMatch(input + 1, rule);  // *匹配非0个字符
			if ((may >= 0) && (++may > r))
			{
				r = may;
			}
		}
	}
	if (*input == 0)
	{
		//到尾端
		return r;
	}
	if ((*rule == '?') || (*rule == *input))
	{
		may = canMatch(input + 1, rule + 1);
		if ((may >= 0) && (++may > r))
		{
			r = may;
		}
	}
	return r;
}