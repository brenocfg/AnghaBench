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
struct loadedfile {int dummy; } ;
struct TYPE_2__ {int lineno; struct loadedfile* lf; } ;

/* Variables and functions */
 scalar_t__ CONTINUE ; 
 scalar_t__ DEBUG (int /*<<< orphan*/ ) ; 
 scalar_t__ FALSE ; 
 scalar_t__ IsInclude (char*,scalar_t__) ; 
 scalar_t__ IsSysVInclude (char*) ; 
 int /*<<< orphan*/  Lst_AtEnd (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  Lst_Destroy (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Lst_ForEach (scalar_t__,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ Lst_Init (scalar_t__) ; 
 int /*<<< orphan*/  PARSE ; 
 int /*<<< orphan*/  PARSE_FATAL ; 
 int /*<<< orphan*/  PARSE_WARNING ; 
 int /*<<< orphan*/  ParseAddCmd ; 
 int /*<<< orphan*/  ParseDoDependency (char*) ; 
 int /*<<< orphan*/  ParseDoInclude (char*) ; 
 scalar_t__ ParseEOF () ; 
 int /*<<< orphan*/  ParseFinishLine () ; 
 int /*<<< orphan*/  ParseGmakeExport (char*) ; 
 scalar_t__ ParseIsEscaped (char*,char*) ; 
 scalar_t__ ParseMessage (char*) ; 
 char* ParseReadLine () ; 
 int /*<<< orphan*/  ParseTraditionalInclude (char*) ; 
 int /*<<< orphan*/  Parse_DoVar (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Parse_Error (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ Parse_IsVar (char*) ; 
 int /*<<< orphan*/  Parse_SetInput (char const*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct loadedfile*) ; 
 int /*<<< orphan*/  PrintOnError (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ TRUE ; 
 int VARF_UNDEFERR ; 
 int VARF_WANTRES ; 
 int /*<<< orphan*/  VAR_CMD ; 
 int /*<<< orphan*/  VAR_GLOBAL ; 
 int /*<<< orphan*/  Var_Delete (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Var_Export (char*,int) ; 
 char* Var_Subst (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Var_UnExport (char*) ; 
 char* bmake_strdup (char*) ; 
 TYPE_1__* curFile ; 
 int /*<<< orphan*/  debug_file ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ fatals ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ inLine ; 
 scalar_t__ isspace (unsigned char) ; 
 int /*<<< orphan*/  loadedfile_nextbuf ; 
 struct loadedfile* loadfile (char const*,int) ; 
 char* progname ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/ * strchr (char*,char) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 int /*<<< orphan*/  targCmds ; 
 scalar_t__ targets ; 

void
Parse_File(const char *name, int fd)
{
    char	  *cp;		/* pointer into the line */
    char          *line;	/* the line we're working on */
    struct loadedfile *lf;

    lf = loadfile(name, fd);

    inLine = FALSE;
    fatals = 0;

    if (name == NULL) {
	    name = "(stdin)";
    }

    Parse_SetInput(name, 0, -1, loadedfile_nextbuf, lf);
    curFile->lf = lf;

    do {
	for (; (line = ParseReadLine()) != NULL; ) {
	    if (DEBUG(PARSE))
		fprintf(debug_file, "ParseReadLine (%d): '%s'\n",
			curFile->lineno, line);
	    if (*line == '.') {
		/*
		 * Lines that begin with the special character may be
		 * include or undef directives.
		 * On the other hand they can be suffix rules (.c.o: ...)
		 * or just dependencies for filenames that start '.'.
		 */
		for (cp = line + 1; isspace((unsigned char)*cp); cp++) {
		    continue;
		}
		if (IsInclude(cp, FALSE)) {
		    ParseDoInclude(cp);
		    continue;
		}
		if (strncmp(cp, "undef", 5) == 0) {
		    char *cp2;
		    for (cp += 5; isspace((unsigned char) *cp); cp++)
			continue;
		    for (cp2 = cp; !isspace((unsigned char) *cp2) &&
				   (*cp2 != '\0'); cp2++)
			continue;
		    *cp2 = '\0';
		    Var_Delete(cp, VAR_GLOBAL);
		    continue;
		} else if (strncmp(cp, "export", 6) == 0) {
		    for (cp += 6; isspace((unsigned char) *cp); cp++)
			continue;
		    Var_Export(cp, 1);
		    continue;
		} else if (strncmp(cp, "unexport", 8) == 0) {
		    Var_UnExport(cp);
		    continue;
		} else if (strncmp(cp, "info", 4) == 0 ||
			   strncmp(cp, "error", 5) == 0 ||
			   strncmp(cp, "warning", 7) == 0) {
		    if (ParseMessage(cp))
			continue;
		}		    
	    }

	    if (*line == '\t') {
		/*
		 * If a line starts with a tab, it can only hope to be
		 * a creation command.
		 */
		cp = line + 1;
	      shellCommand:
		for (; isspace ((unsigned char)*cp); cp++) {
		    continue;
		}
		if (*cp) {
		    if (!inLine)
			Parse_Error(PARSE_FATAL,
				     "Unassociated shell command \"%s\"",
				     cp);
		    /*
		     * So long as it's not a blank line and we're actually
		     * in a dependency spec, add the command to the list of
		     * commands of all targets in the dependency spec
		     */
		    if (targets) {
			cp = bmake_strdup(cp);
			Lst_ForEach(targets, ParseAddCmd, cp);
#ifdef CLEANUP
			Lst_AtEnd(targCmds, cp);
#endif
		    }
		}
		continue;
	    }

#ifdef SYSVINCLUDE
	    if (IsSysVInclude(line)) {
		/*
		 * It's an S3/S5-style "include".
		 */
		ParseTraditionalInclude(line);
		continue;
	    }
#endif
#ifdef GMAKEEXPORT
	    if (strncmp(line, "export", 6) == 0 &&
		isspace((unsigned char) line[6]) &&
		strchr(line, ':') == NULL) {
		/*
		 * It's a Gmake "export".
		 */
		ParseGmakeExport(line);
		continue;
	    }
#endif
	    if (Parse_IsVar(line)) {
		ParseFinishLine();
		Parse_DoVar(line, VAR_GLOBAL);
		continue;
	    }

#ifndef POSIX
	    /*
	     * To make life easier on novices, if the line is indented we
	     * first make sure the line has a dependency operator in it.
	     * If it doesn't have an operator and we're in a dependency
	     * line's script, we assume it's actually a shell command
	     * and add it to the current list of targets.
	     */
	    cp = line;
	    if (isspace((unsigned char) line[0])) {
		while ((*cp != '\0') && isspace((unsigned char) *cp))
		    cp++;
		while (*cp && (ParseIsEscaped(line, cp) ||
			(*cp != ':') && (*cp != '!'))) {
		    cp++;
		}
		if (*cp == '\0') {
		    if (inLine) {
			Parse_Error(PARSE_WARNING,
				     "Shell command needs a leading tab");
			goto shellCommand;
		    }
		}
	    }
#endif
	    ParseFinishLine();

	    /*
	     * For some reason - probably to make the parser impossible -
	     * a ';' can be used to separate commands from dependencies.
	     * Attempt to avoid ';' inside substitution patterns.
	     */
	    {
		int level = 0;

		for (cp = line; *cp != 0; cp++) {
		    if (*cp == '\\' && cp[1] != 0) {
			cp++;
			continue;
		    }
		    if (*cp == '$' &&
			(cp[1] == '(' || cp[1] == '{')) {
			level++;
			continue;
		    }
		    if (level > 0) {
			if (*cp == ')' || *cp == '}') {
			    level--;
			    continue;
			}
		    } else if (*cp == ';') {
			break;
		    }
		}
	    }
	    if (*cp != 0)
		/* Terminate the dependency list at the ';' */
		*cp++ = 0;
	    else
		cp = NULL;

	    /*
	     * We now know it's a dependency line so it needs to have all
	     * variables expanded before being parsed. Tell the variable
	     * module to complain if some variable is undefined...
	     */
	    line = Var_Subst(NULL, line, VAR_CMD, VARF_UNDEFERR|VARF_WANTRES);

	    /*
	     * Need a non-circular list for the target nodes
	     */
	    if (targets)
		Lst_Destroy(targets, NULL);

	    targets = Lst_Init(FALSE);
	    inLine = TRUE;

	    ParseDoDependency(line);
	    free(line);

	    /* If there were commands after a ';', add them now */
	    if (cp != NULL) {
		goto shellCommand;
	    }
	}
	/*
	 * Reached EOF, but it may be just EOF of an include file...
	 */
    } while (ParseEOF() == CONTINUE);

    if (fatals) {
	(void)fflush(stdout);
	(void)fprintf(stderr,
	    "%s: Fatal errors encountered -- cannot continue",
	    progname);
	PrintOnError(NULL, NULL);
	exit(1);
    }
}