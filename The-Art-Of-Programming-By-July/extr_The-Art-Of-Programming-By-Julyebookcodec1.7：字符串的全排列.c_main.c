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
 scalar_t__ CalcAllPermutation (char*,int) ; 
 char cout ; 
 char endl ; 

int main()
{
	char a[] = "123";
	do{
		for (int i = 0; i < 3; ++i)
			cout << a[i];
		cout << endl;
	} while (CalcAllPermutation(a, 3));
	return 0;
}