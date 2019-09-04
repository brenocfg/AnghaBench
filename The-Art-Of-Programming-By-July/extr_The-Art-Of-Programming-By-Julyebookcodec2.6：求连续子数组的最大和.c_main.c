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
 int cout ; 
 int endl ; 
 int maxSubArray (int*,int) ; 

int main()
{
	int a[] = { 1, -2, 3, 10, -4, 7, 2, -5 };
	cout << maxSubArray(a, 8) << endl;
	//int a[] = { -1, -2, -3, -4 };
	//cout << maxSubArray(a,4) << endl;
	return 0;
}