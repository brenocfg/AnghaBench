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
 int EXPECT ; 
 int EXPECT_RR ; 
 void* RRexpect ; 
 void* SRexpect ; 
 int* cptr ; 
 void* get_number () ; 
 scalar_t__ isalpha (int) ; 
 scalar_t__ isdigit (int) ; 
 int /*<<< orphan*/  isspace (int) ; 
 int /*<<< orphan*/  line ; 
 int /*<<< orphan*/  lineno ; 
 int /*<<< orphan*/  prec ; 
 int /*<<< orphan*/  syntax_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  unexpected_EOF () ; 

__attribute__((used)) static void
declare_expect(int assoc)
{
    int c;

    if (assoc != EXPECT && assoc != EXPECT_RR)
	++prec;

    /*
     * Stay away from nextc - doesn't
     * detect EOL and will read to EOF.
     */
    c = *++cptr;
    if (c == EOF)
	unexpected_EOF();

    for (;;)
    {
	if (isdigit(c))
	{
	    if (assoc == EXPECT)
		SRexpect = get_number();
	    else
		RRexpect = get_number();
	    break;
	}
	/*
	 * Looking for number before EOL.
	 * Spaces, tabs, and numbers are ok,
	 * words, punc., etc. are syntax errors.
	 */
	else if (c == '\n' || isalpha(c) || !isspace(c))
	{
	    syntax_error(lineno, line, cptr);
	}
	else
	{
	    c = *++cptr;
	    if (c == EOF)
		unexpected_EOF();
	}
    }
}