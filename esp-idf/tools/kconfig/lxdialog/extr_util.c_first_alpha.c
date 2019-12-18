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
 scalar_t__ isalpha (int) ; 
 scalar_t__ strchr (char const*,int) ; 
 int strlen (char const*) ; 
 int tolower (char const) ; 

int first_alpha(const char *string, const char *exempt)
{
	int i, in_paren = 0, c;

	for (i = 0; i < strlen(string); i++) {
		c = tolower(string[i]);

		if (strchr("<[(", c))
			++in_paren;
		if (strchr(">])", c) && in_paren > 0)
			--in_paren;

		if ((!in_paren) && isalpha(c) && strchr(exempt, c) == 0)
			return i;
	}

	return 0;
}