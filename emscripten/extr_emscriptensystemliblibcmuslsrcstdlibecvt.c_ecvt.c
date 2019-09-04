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
 int atoi (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,double) ; 

char *ecvt(double x, int n, int *dp, int *sign)
{
	static char buf[16];
	char tmp[32];
	int i, j;

	if (n-1U > 15) n = 15;
	sprintf(tmp, "%.*e", n-1, x);
	i = *sign = (tmp[0]=='-');
	for (j=0; tmp[i]!='e'; j+=(tmp[i++]!='.'))
		buf[j] = tmp[i];
	buf[j] = 0;
	*dp = atoi(tmp+i+1)+1;

	return buf;
}