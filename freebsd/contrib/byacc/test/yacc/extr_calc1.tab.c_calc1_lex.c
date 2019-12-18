#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int ival; int /*<<< orphan*/  dval; } ;

/* Variables and functions */
 int BSZ ; 
 int CONST ; 
 int DREG ; 
 int VREG ; 
 int /*<<< orphan*/  atof (char*) ; 
 int getchar () ; 
 scalar_t__ isdigit (int) ; 
 scalar_t__ islower (int) ; 
 scalar_t__ isupper (int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  ungetc (int,int /*<<< orphan*/ ) ; 
 TYPE_1__ yylval ; 

int
yylex(void)
{
    int c;

    while ((c = getchar()) == ' ')
    {				/* skip over blanks */
    }

    if (isupper(c))
    {
	yylval.ival = c - 'A';
	return (VREG);
    }
    if (islower(c))
    {
	yylval.ival = c - 'a';
	return (DREG);
    }

    if (isdigit(c) || c == '.')
    {
	/* gobble up digits, points, exponents */
	char buf[BSZ + 1], *cp = buf;
	int dot = 0, expr = 0;

	for (; (cp - buf) < BSZ; ++cp, c = getchar())
	{

	    *cp = (char) c;
	    if (isdigit(c))
		continue;
	    if (c == '.')
	    {
		if (dot++ || expr)
		    return ('.');	/* will cause syntax error */
		continue;
	    }

	    if (c == 'e')
	    {
		if (expr++)
		    return ('e');	/*  will  cause  syntax  error  */
		continue;
	    }

	    /*  end  of  number  */
	    break;
	}
	*cp = '\0';

	if ((cp - buf) >= BSZ)
	    printf("constant  too  long:  truncated\n");
	else
	    ungetc(c, stdin);	/*  push  back  last  char  read  */
	yylval.dval = atof(buf);
	return (CONST);
    }
    return (c);
}