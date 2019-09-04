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
 int /*<<< orphan*/  printf (char*,int,int) ; 

void twoSum(int data[], unsigned int length, int sum)
{
	//sort(s, s+n);   如果数组非有序的，那就事先排好序O(N log N)

	int begin = 0;
	int end = length - 1;

	//俩头夹逼，或称两个指针两端扫描法，很经典的方法，O(N)
	while (begin < end)
	{
		long currSum = data[begin] + data[end];

		if (currSum == sum)
		{
			//题目只要求输出满足条件的任意一对即可
			printf("%d %d\n", data[begin], data[end]);

			//如果需要所有满足条件的数组对，则需要加上下面两条语句：
			//begin++
			//end--
			break;
		}
		else{
			if (currSum < sum)
				begin++;
			else
				end--;
		}
	}
}