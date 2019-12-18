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
struct ainfo {int a_line; int a_cptr; int /*<<< orphan*/  a_lineno; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREE (int) ; 
 char* cptr ; 
 int dup_line () ; 
 int /*<<< orphan*/  get_line () ; 
 char* line ; 
 int /*<<< orphan*/  lineno ; 
 int /*<<< orphan*/  unterminated_comment (struct ainfo*) ; 

__attribute__((used)) static void
skip_comment(void)
{
    char *s;
    struct ainfo a;
    a.a_lineno = lineno;
    a.a_line = dup_line();
    a.a_cptr = a.a_line + (cptr - line);

    s = cptr + 2;
    for (;;)
    {
	if (*s == '*' && s[1] == '/')
	{
	    cptr = s + 2;
	    FREE(a.a_line);
	    return;
	}
	if (*s == '\n')
	{
	    get_line();
	    if (line == NULL)
		unterminated_comment(&a);
	    s = cptr;
	}
	else
	    ++s;
    }
}