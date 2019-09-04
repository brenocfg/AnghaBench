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

void perfect_shuffle2(int *a, int n)
{
	int t, i;
	if (n == 1)
	{
		t = a[1];
		a[1] = a[2];
		a[2] = t;
		return;
	}
	int n2 = n * 2, n3 = n / 2;
	if (n % 2 == 1)    //奇数的处理
	{
		t = a[n];
		for (i = n + 1; i <= n2; ++i)
		{
			a[i - 1] = a[i];
		}
		a[n2] = t;
		--n;
	}
	//到此n是偶数

	for (i = n3 + 1; i <= n; ++i)
	{
		t = a[i];
		a[i] = a[i + n3];
		a[i + n3] = t;
	}

	// [1.. n /2]
	perfect_shuffle2(a, n3);
	perfect_shuffle2(a + n, n3);
}