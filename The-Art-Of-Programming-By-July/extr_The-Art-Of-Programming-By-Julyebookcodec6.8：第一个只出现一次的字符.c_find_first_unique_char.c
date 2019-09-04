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
typedef  int /*<<< orphan*/  data ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 

char find_first_unique_char(char *str)
{
	int data[256];
	char *p;

	if (str == NULL)
		return '\0';

	memset(data, 0, sizeof(data));    //数组元素先全部初始化为0
	p = str;
	while (*p != '\0')
		data[(unsigned char)*p++]++;  //遍历字符串，在相应位置++，（同时，下标强制转换）

	while (*str != '\0')
	{
		if (data[(unsigned char)*str] == 1)  //最后，输出那个第一个只出现次数为1的字符
			return *str;

		str++;
	}

	return '\0';
}