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
 int* sum ; 

int main()
{
	int i, j;
	for (i = 0; i <= 5000000; i++)
		sum[i] = 1;  //1是所有数的真因数所以全部置1

	for (i = 2; i + i <= 5000000; i++)  //预处理，预处理是logN（调和级数）*N。
		//@litaoye：调和级数1/2 + 1/3 + 1/4......的和近似为ln(n)，
		//因此O(n *(1/2 + 1/3 + 1/4......)) = O(n * ln(n)) = O(N*log(N))。
	{
		//5000000以下最大的真因数是不超过它的一半的
		j = i + i;  //因为真因数，所以不能算本身，所以从它的2倍开始
		while (j <= 5000000)
		{
			//将所有i的倍数的位置上加i
			sum[j] += i;
			j += i;
		}
	}

	for (i = 220; i <= 5000000; i++)   //扫描，O（N）。
	{
		// 一次遍历，因为知道最小是220和284因此从220开始
		if (sum[i] > i && sum[i] <= 5000000 && sum[sum[i]] == i)
		{
			//去重，不越界，满足亲和
			printf("%d %d/n",i,sum[i]);
		}
	}
	return 0;
}