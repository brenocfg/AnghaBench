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
 int FALSE ; 
 int TRUE ; 
 int Util_sscandec (char const*) ; 
 char* get_token () ; 

__attribute__((used)) static int get_dec(int *decval)
{
	const char *t;
	t = get_token();
	if (t != NULL) {
		int x = Util_sscandec(t);
		if (x < 0)
			return FALSE;
		*decval = x;
		return TRUE;
	}
	return FALSE;
}