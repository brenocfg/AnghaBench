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
 int MAKETYPEID (int,int) ; 
 int /*<<< orphan*/  expected (char*,char*,char*) ; 
 scalar_t__ isdigit (char) ; 
 char* number (char*,int*) ; 

__attribute__((used)) static char *
id(char *cp, int *h)
{
	int n1, n2;

	if (*cp == '(') {	/* SunPro style */
		cp++;
		cp = number(cp, &n1);
		if (*cp++ != ',')
			expected("id", ",", cp - 1);
		cp = number(cp, &n2);
		if (*cp++ != ')')
			expected("id", ")", cp - 1);
		*h = MAKETYPEID(n1, n2);
	} else if (isdigit(*cp)) { /* gcc style */
		cp = number(cp, &n1);
		*h = n1;
	} else {
		expected("id", "(/0-9", cp);
	}
	return (cp);
}