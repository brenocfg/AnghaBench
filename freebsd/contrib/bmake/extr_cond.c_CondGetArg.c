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
typedef  int /*<<< orphan*/  Buffer ;

/* Variables and functions */
 int /*<<< orphan*/  Buf_AddByte (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  Buf_AddBytes (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  Buf_Destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* Buf_GetAll (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  Buf_Init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  PARSE_WARNING ; 
 int /*<<< orphan*/  Parse_Error (int /*<<< orphan*/ ,char*,char const*) ; 
 int VARF_UNDEFERR ; 
 int VARF_WANTRES ; 
 int /*<<< orphan*/  VAR_CMD ; 
 char* Var_Parse (char*,int /*<<< orphan*/ ,int,int*,void**) ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static int
CondGetArg(char **linePtr, char **argPtr, const char *func)
{
    char	  *cp;
    int	    	  argLen;
    Buffer	  buf;
    int           paren_depth;
    char          ch;

    cp = *linePtr;
    if (func != NULL)
	/* Skip opening '(' - verfied by caller */
	cp++;

    if (*cp == '\0') {
	/*
	 * No arguments whatsoever. Because 'make' and 'defined' aren't really
	 * "reserved words", we don't print a message. I think this is better
	 * than hitting the user with a warning message every time s/he uses
	 * the word 'make' or 'defined' at the beginning of a symbol...
	 */
	*argPtr = NULL;
	return (0);
    }

    while (*cp == ' ' || *cp == '\t') {
	cp++;
    }

    /*
     * Create a buffer for the argument and start it out at 16 characters
     * long. Why 16? Why not?
     */
    Buf_Init(&buf, 16);

    paren_depth = 0;
    for (;;) {
	ch = *cp;
	if (ch == 0 || ch == ' ' || ch == '\t')
	    break;
	if ((ch == '&' || ch == '|') && paren_depth == 0)
	    break;
	if (*cp == '$') {
	    /*
	     * Parse the variable spec and install it as part of the argument
	     * if it's valid. We tell Var_Parse to complain on an undefined
	     * variable, so we don't do it too. Nor do we return an error,
	     * though perhaps we should...
	     */
	    char  	*cp2;
	    int		len;
	    void	*freeIt;

	    cp2 = Var_Parse(cp, VAR_CMD, VARF_UNDEFERR|VARF_WANTRES,
			    &len, &freeIt);
	    Buf_AddBytes(&buf, strlen(cp2), cp2);
	    free(freeIt);
	    cp += len;
	    continue;
	}
	if (ch == '(')
	    paren_depth++;
	else
	    if (ch == ')' && --paren_depth < 0)
		break;
	Buf_AddByte(&buf, *cp);
	cp++;
    }

    *argPtr = Buf_GetAll(&buf, &argLen);
    Buf_Destroy(&buf, FALSE);

    while (*cp == ' ' || *cp == '\t') {
	cp++;
    }

    if (func != NULL && *cp++ != ')') {
	Parse_Error(PARSE_WARNING, "Missing closing parenthesis for %s()",
		     func);
	return (0);
    }

    *linePtr = cp;
    return (argLen);
}