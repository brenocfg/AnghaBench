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
 int /*<<< orphan*/  cycle_leader (int*,int,int) ; 
 int /*<<< orphan*/  right_rotate (int*,int,int) ; 

void perfect_shuffle3(int *a, int n)
{
	int n2, m, i, k, t;
	for (; n > 1;)
	{
		// step 1
		n2 = n * 2;
		for (k = 0, m = 1; n2 / m >= 3; ++k, m *= 3)
			;
		m /= 2;
		// 2m = 3^k - 1 , 3^k <= 2n < 3^(k + 1)

		// step 2
		right_rotate(a + m, m, n);

		// step 3
		for (i = 0, t = 1; i < k; ++i, t *= 3)
		{
			cycle_leader(a , t, m * 2 + 1);
		}

		//step 4
		a += m * 2;
		n -= m;

	}
	// n = 1
	t = a[1];
	a[1] = a[2];
	a[2] = t;
}