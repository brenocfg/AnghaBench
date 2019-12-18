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
struct mstring {int dummy; } ;
struct ainfo {int a_line; int a_cptr; int /*<<< orphan*/  a_lineno; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREE (int) ; 
 char* cptr ; 
 int dup_line () ; 
 int /*<<< orphan*/  get_line () ; 
 char* line ; 
 int /*<<< orphan*/  lineno ; 
 int /*<<< orphan*/  mputc (struct mstring*,char) ; 
 char* msdone (struct mstring*) ; 
 struct mstring* msnew () ; 
 int /*<<< orphan*/  unterminated_comment (struct ainfo*) ; 

__attribute__((used)) static char *
copy_comment(void)
{
    struct mstring *temp = msnew();
    int c;

    c = *cptr;
    if (c == '/')
    {
	mputc(temp, '*');
	while ((c = *++cptr) != '\n')
	{
	    mputc(temp, c);
	    if (c == '*' && cptr[1] == '/')
		mputc(temp, ' ');
	}
	mputc(temp, '*');
	mputc(temp, '/');
    }
    else if (c == '*')
    {
	struct ainfo a;
	a.a_lineno = lineno;
	a.a_line = dup_line();
	a.a_cptr = a.a_line + (cptr - line - 1);

	mputc(temp, c);
	++cptr;
	for (;;)
	{
	    c = *cptr++;
	    mputc(temp, c);
	    if (c == '*' && *cptr == '/')
	    {
		mputc(temp, '/');
		++cptr;
		FREE(a.a_line);
		return msdone(temp);
	    }
	    if (c == '\n')
	    {
		get_line();
		if (line == NULL)
		    unterminated_comment(&a);
	    }
	}
    }
    return msdone(temp);
}