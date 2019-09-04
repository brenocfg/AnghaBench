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
typedef  int /*<<< orphan*/  _TCHAR ;

/* Variables and functions */
 int cout ; 
 int endl ; 
 int maxProductSubstring (double*,int) ; 

int _tmain(int argc, _TCHAR* argv[])
{
	double a[] = { -3, -0.5,- 10};
	cout << maxProductSubstring(a, 3) << endl;
	return 0;
}