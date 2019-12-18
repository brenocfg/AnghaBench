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
 int /*<<< orphan*/  isspace (char) ; 
 int strlen (char*) ; 

char* StripPreSuffixWhitespace(char* string)
{
	char* p;
	for (;;)
	{
		if (string[0] == 0 || !isspace(string[0]))
			break;
		string++;
	}

	if (strlen(string) == 0)
		return string;

	p = string+strlen(string)-1;
	for (;;)
	{
		if (p <= string || !isspace(p[0]))
		{
			p[1] = '\0';
			break;
		}
		p--;
	}

	return string;
}