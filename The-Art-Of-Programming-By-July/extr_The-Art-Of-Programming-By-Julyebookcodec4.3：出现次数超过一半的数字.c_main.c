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
 int FindOneNumber (int*,int) ; 
 int cout ; 
 int endl ; 

int main()
{
	int a[10] = { 1, 2, 3, 4, 6, 6, 6, 6, 6 };
	int* n = a;
	cout << FindOneNumber(a, 9) << endl;
	return 0;
}