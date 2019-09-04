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

int binary_search(int array[], int n, int value)
{
	int left = 0;
	int right = n - 1;
	//如果这里是int right = n 的话，那么下面有两处地方需要修改，以保证一一对应：
	//1、下面循环的条件则是while(left < right)
	//2、循环内当 array[middle] > value 的时候，right = mid

	while (left <= right)  //循环条件，适时而变
	{
		int middle = left + ((right - left) >> 1);  //防止溢出，移位也更高效。同时，每次循环都需要更新。

		if (array[middle] > value)
		{
			right = middle - 1;  //right赋值，适时而变
		}
		else if(array[middle] < value)
		{
			left = middle + 1;
		}
		else
			return middle;
		//可能会有读者认为刚开始时就要判断相等，但毕竟数组中不相等的情况更多
		//如果每次循环都判断一下是否相等，将耗费时间
	}
	return -1;
}