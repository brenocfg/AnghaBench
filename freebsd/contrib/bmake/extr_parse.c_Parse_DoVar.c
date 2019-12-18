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
typedef  int /*<<< orphan*/  GNode ;
typedef  void* Boolean ;

/* Variables and functions */
 char* Cmd_Exec (char*,char const**) ; 
 int /*<<< orphan*/  Dir_InitCur (char*) ; 
 int /*<<< orphan*/  Dir_SetPATH () ; 
 void* FALSE ; 
 int /*<<< orphan*/  Job_SetPrefix () ; 
 char* MAKEOVERRIDES ; 
 char* MAKE_EXPORTED ; 
 char* MAKE_JOB_PREFIX ; 
 int /*<<< orphan*/  Main_ExportMAKEFLAGS (void*) ; 
 int /*<<< orphan*/  PARSE_WARNING ; 
 int /*<<< orphan*/  Parse_Error (int /*<<< orphan*/ ,char const*,char*) ; 
 void* TRUE ; 
 int VARF_ASSIGN ; 
 int VARF_UNDEFERR ; 
 int VARF_WANTRES ; 
 int /*<<< orphan*/ * VAR_CMD ; 
 int /*<<< orphan*/  Var_Append (char*,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ Var_Exists (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Var_Export (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Var_Set (char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* Var_Subst (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ isspace (unsigned char) ; 
 void* oldVars ; 
 int /*<<< orphan*/ * strchr (char*,char) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 

void
Parse_DoVar(char *line, GNode *ctxt)
{
    char	   *cp;	/* pointer into line */
    enum {
	VAR_SUBST, VAR_APPEND, VAR_SHELL, VAR_NORMAL
    }	    	    type;   	/* Type of assignment */
    char            *opc;	/* ptr to operator character to
				 * null-terminate the variable name */
    Boolean	   freeCp = FALSE; /* TRUE if cp needs to be freed,
				    * i.e. if any variable expansion was
				    * performed */
    int depth;

    /*
     * Skip to variable name
     */
    while ((*line == ' ') || (*line == '\t')) {
	line++;
    }

    /*
     * Skip to operator character, nulling out whitespace as we go
     * XXX Rather than counting () and {} we should look for $ and
     * then expand the variable.
     */
    for (depth = 0, cp = line + 1; depth > 0 || *cp != '='; cp++) {
	if (*cp == '(' || *cp == '{') {
	    depth++;
	    continue;
	}
	if (*cp == ')' || *cp == '}') {
	    depth--;
	    continue;
	}
	if (depth == 0 && isspace ((unsigned char)*cp)) {
	    *cp = '\0';
	}
    }
    opc = cp-1;		/* operator is the previous character */
    *cp++ = '\0';	/* nuke the = */

    /*
     * Check operator type
     */
    switch (*opc) {
	case '+':
	    type = VAR_APPEND;
	    *opc = '\0';
	    break;

	case '?':
	    /*
	     * If the variable already has a value, we don't do anything.
	     */
	    *opc = '\0';
	    if (Var_Exists(line, ctxt)) {
		return;
	    } else {
		type = VAR_NORMAL;
	    }
	    break;

	case ':':
	    type = VAR_SUBST;
	    *opc = '\0';
	    break;

	case '!':
	    type = VAR_SHELL;
	    *opc = '\0';
	    break;

	default:
#ifdef SUNSHCMD
	    while (opc > line && *opc != ':')
		opc--;

	    if (strncmp(opc, ":sh", 3) == 0) {
		type = VAR_SHELL;
		*opc = '\0';
		break;
	    }
#endif
	    type = VAR_NORMAL;
	    break;
    }

    while (isspace ((unsigned char)*cp)) {
	cp++;
    }

    if (type == VAR_APPEND) {
	Var_Append(line, cp, ctxt);
    } else if (type == VAR_SUBST) {
	/*
	 * Allow variables in the old value to be undefined, but leave their
	 * invocation alone -- this is done by forcing oldVars to be false.
	 * XXX: This can cause recursive variables, but that's not hard to do,
	 * and this allows someone to do something like
	 *
	 *  CFLAGS = $(.INCLUDES)
	 *  CFLAGS := -I.. $(CFLAGS)
	 *
	 * And not get an error.
	 */
	Boolean	  oldOldVars = oldVars;

	oldVars = FALSE;

	/*
	 * make sure that we set the variable the first time to nothing
	 * so that it gets substituted!
	 */
	if (!Var_Exists(line, ctxt))
	    Var_Set(line, "", ctxt, 0);

	cp = Var_Subst(NULL, cp, ctxt, VARF_WANTRES|VARF_ASSIGN);
	oldVars = oldOldVars;
	freeCp = TRUE;

	Var_Set(line, cp, ctxt, 0);
    } else if (type == VAR_SHELL) {
	char *res;
	const char *error;

	if (strchr(cp, '$') != NULL) {
	    /*
	     * There's a dollar sign in the command, so perform variable
	     * expansion on the whole thing. The resulting string will need
	     * freeing when we're done, so set freeCmd to TRUE.
	     */
	    cp = Var_Subst(NULL, cp, VAR_CMD, VARF_UNDEFERR|VARF_WANTRES);
	    freeCp = TRUE;
	}

	res = Cmd_Exec(cp, &error);
	Var_Set(line, res, ctxt, 0);
	free(res);

	if (error)
	    Parse_Error(PARSE_WARNING, error, cp);
    } else {
	/*
	 * Normal assignment -- just do it.
	 */
	Var_Set(line, cp, ctxt, 0);
    }
    if (strcmp(line, MAKEOVERRIDES) == 0)
	Main_ExportMAKEFLAGS(FALSE);	/* re-export MAKEFLAGS */
    else if (strcmp(line, ".CURDIR") == 0) {
	/*
	 * Somone is being (too?) clever...
	 * Let's pretend they know what they are doing and
	 * re-initialize the 'cur' Path.
	 */
	Dir_InitCur(cp);
	Dir_SetPATH();
    } else if (strcmp(line, MAKE_JOB_PREFIX) == 0) {
	Job_SetPrefix();
    } else if (strcmp(line, MAKE_EXPORTED) == 0) {
	Var_Export(cp, 0);
    }
    if (freeCp)
	free(cp);
}