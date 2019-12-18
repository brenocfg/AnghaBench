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
struct TYPE_2__ {int lineno; } ;

/* Variables and functions */
#define  COND_INVALID 130 
#define  COND_PARSE 129 
#define  COND_SKIP 128 
 int Cond_Eval (char*) ; 
 int /*<<< orphan*/  For_Accum (char*) ; 
 int For_Eval (char*) ; 
 int /*<<< orphan*/  For_Run (int) ; 
 int /*<<< orphan*/  PARSE_FATAL ; 
 int /*<<< orphan*/  PARSE_RAW ; 
 int /*<<< orphan*/  PARSE_SKIP ; 
 char* ParseGetLine (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  Parse_Error (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* curFile ; 

__attribute__((used)) static char *
ParseReadLine(void)
{
    char 	  *line;    	/* Result */
    int	    	  lineLength;	/* Length of result */
    int	    	  lineno;	/* Saved line # */
    int	    	  rval;

    for (;;) {
	line = ParseGetLine(0, &lineLength);
	if (line == NULL)
	    return NULL;

	if (line[0] != '.')
	    return line;

	/*
	 * The line might be a conditional. Ask the conditional module
	 * about it and act accordingly
	 */
	switch (Cond_Eval(line)) {
	case COND_SKIP:
	    /* Skip to next conditional that evaluates to COND_PARSE.  */
	    do {
		line = ParseGetLine(PARSE_SKIP, &lineLength);
	    } while (line && Cond_Eval(line) != COND_PARSE);
	    if (line == NULL)
		break;
	    continue;
	case COND_PARSE:
	    continue;
	case COND_INVALID:    /* Not a conditional line */
	    /* Check for .for loops */
	    rval = For_Eval(line);
	    if (rval == 0)
		/* Not a .for line */
		break;
	    if (rval < 0)
		/* Syntax error - error printed, ignore line */
		continue;
	    /* Start of a .for loop */
	    lineno = curFile->lineno;
	    /* Accumulate loop lines until matching .endfor */
	    do {
		line = ParseGetLine(PARSE_RAW, &lineLength);
		if (line == NULL) {
		    Parse_Error(PARSE_FATAL,
			     "Unexpected end of file in for loop.");
		    break;
		}
	    } while (For_Accum(line));
	    /* Stash each iteration as a new 'input file' */
	    For_Run(lineno);
	    /* Read next line from for-loop buffer */
	    continue;
	}
	return (line);
    }
}