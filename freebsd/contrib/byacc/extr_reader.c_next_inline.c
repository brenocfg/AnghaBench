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
 int EOF ; 
 char* cptr ; 
 int /*<<< orphan*/  get_line () ; 
 int /*<<< orphan*/ * line ; 
 int /*<<< orphan*/  skip_comment () ; 

__attribute__((used)) static int
next_inline(void)
{
    char *s;

    if (line == NULL)
    {
	get_line();
	if (line == NULL)
	    return (EOF);
    }

    s = cptr;
    for (;;)
    {
	switch (*s)
	{
	case '/':
	    if (s[1] == '*')
	    {
		cptr = s;
		skip_comment();
		s = cptr;
		break;
	    }
	    else if (s[1] == '/')
	    {
		get_line();
		if (line == NULL)
		    return (EOF);
		s = cptr;
		break;
	    }
	    /* FALLTHRU */

	default:
	    cptr = s;
	    return (*s);
	}
    }
}