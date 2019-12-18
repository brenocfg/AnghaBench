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
 int /*<<< orphan*/  PARSE_FATAL ; 
 int /*<<< orphan*/  Parse_Error (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  Parse_include_file (char*,int,int,int) ; 
 int /*<<< orphan*/  VARF_WANTRES ; 
 int /*<<< orphan*/  VAR_CMD ; 
 char* Var_Subst (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 

__attribute__((used)) static void
ParseDoInclude(char *line)
{
    char          endc;	    	/* the character which ends the file spec */
    char          *cp;		/* current position in file spec */
    int		  silent = (*line != 'i') ? 1 : 0;
    char	  *file = &line[7 + silent];

    /* Skip to delimiter character so we know where to look */
    while (*file == ' ' || *file == '\t')
	file++;

    if (*file != '"' && *file != '<') {
	Parse_Error(PARSE_FATAL,
	    ".include filename must be delimited by '\"' or '<'");
	return;
    }

    /*
     * Set the search path on which to find the include file based on the
     * characters which bracket its name. Angle-brackets imply it's
     * a system Makefile while double-quotes imply it's a user makefile
     */
    if (*file == '<') {
	endc = '>';
    } else {
	endc = '"';
    }

    /* Skip to matching delimiter */
    for (cp = ++file; *cp && *cp != endc; cp++)
	continue;

    if (*cp != endc) {
	Parse_Error(PARSE_FATAL,
		     "Unclosed %cinclude filename. '%c' expected",
		     '.', endc);
	return;
    }
    *cp = '\0';

    /*
     * Substitute for any variables in the file name before trying to
     * find the thing.
     */
    file = Var_Subst(NULL, file, VAR_CMD, VARF_WANTRES);

    Parse_include_file(file, endc == '>', (*line == 'd'), silent);
    free(file);
}