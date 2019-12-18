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
 int ERR ; 
 int GPR ; 
 int GSG ; 
 int /*<<< orphan*/  STRTOL (long,char*) ; 
 int /*<<< orphan*/ * extract_subst_template () ; 
 char* ibufp ; 
 scalar_t__ rhbufi ; 

int
extract_subst_tail(int *flagp, long *np)
{
	char delimiter;

	*flagp = *np = 0;
	if ((delimiter = *ibufp) == '\n') {
		rhbufi = 0;
		*flagp = GPR;
		return 0;
	} else if (extract_subst_template() == NULL)
		return  ERR;
	else if (*ibufp == '\n') {
		*flagp = GPR;
		return 0;
	} else if (*ibufp == delimiter)
		ibufp++;
	if ('1' <= *ibufp && *ibufp <= '9') {
		STRTOL(*np, ibufp);
		return 0;
	} else if (*ibufp == 'g') {
		ibufp++;
		*flagp = GSG;
		return 0;
	}
	return 0;
}