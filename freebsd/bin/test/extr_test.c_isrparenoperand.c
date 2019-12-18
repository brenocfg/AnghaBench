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
 int nargc ; 
 int parenlevel ; 
 scalar_t__ strcmp (char*,char*) ; 
 char** t_wp ; 

__attribute__((used)) static int
isrparenoperand(void)
{
	char *s;

	if (nargc == 1)
		return 0;
	s = *(t_wp + 1);
	if (nargc == 2)
		return parenlevel == 1 && strcmp(s, ")") == 0;
	return 0;
}