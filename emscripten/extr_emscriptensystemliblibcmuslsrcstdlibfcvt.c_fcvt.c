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
 char* ecvt (double,int,int*,int*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,double) ; 
 scalar_t__ strcspn (char*,char*) ; 
 int strspn (char*,char*) ; 

char *fcvt(double x, int n, int *dp, int *sign)
{
	char tmp[1500];
	int i, lz;

	if (n > 1400U) n = 1400;
	sprintf(tmp, "%.*f", n, x);
	i = (tmp[0] == '-');
	if (tmp[i] == '0') lz = strspn(tmp+i+2, "0");
	else lz = -(int)strcspn(tmp+i, ".");

	if (n<=lz) {
		*sign = i;
		*dp = 1;
		if (n>14U) n = 14;
		return "000000000000000"+14-n;
	}

	return ecvt(x, n-lz, dp, sign);
}