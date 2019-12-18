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
 int /*<<< orphan*/  UCH (char) ; 
 char* after_blanks (char*) ; 
 scalar_t__ isspace (int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static int
trim_blanks(char *buffer)
{
    if (*buffer != '\0')
    {
	char *d = buffer;
	char *s = after_blanks(d);

	while ((*d++ = *s++) != '\0')
	{
	    ;
	}

	--d;
	while ((--d != buffer) && isspace(UCH(*d)))
	    *d = '\0';

	for (s = d = buffer; (*d++ = *s++) != '\0';)
	{
	    if (isspace(UCH(*s)))
	    {
		*s = ' ';
		while (isspace(UCH(*s)))
		{
		    *s++ = ' ';
		}
		--s;
	    }
	}
    }

    return (int)strlen(buffer) - 1;
}