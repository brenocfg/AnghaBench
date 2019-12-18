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
typedef  int /*<<< orphan*/  Boolean ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int PARSE_FATAL ; 
 int PARSE_INFO ; 
 int PARSE_WARNING ; 
 int /*<<< orphan*/  Parse_Error (int,char*,char*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  VARF_WANTRES ; 
 int /*<<< orphan*/  VAR_CMD ; 
 char* Var_Subst (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ isalpha (unsigned char) ; 
 scalar_t__ isspace (unsigned char) ; 

__attribute__((used)) static Boolean
ParseMessage(char *line)
{
    int mtype;

    switch(*line) {
    case 'i':
	mtype = PARSE_INFO;
	break;
    case 'w':
	mtype = PARSE_WARNING;
	break;
    case 'e':
	mtype = PARSE_FATAL;
	break;
    default:
	Parse_Error(PARSE_WARNING, "invalid syntax: \".%s\"", line);
	return FALSE;
    }

    while (isalpha((unsigned char)*line))
	line++;
    if (!isspace((unsigned char)*line))
	return FALSE;			/* not for us */
    while (isspace((unsigned char)*line))
	line++;

    line = Var_Subst(NULL, line, VAR_CMD, VARF_WANTRES);
    Parse_Error(mtype, "%s", line);
    free(line);

    if (mtype == PARSE_FATAL) {
	/* Terminate immediately. */
	exit(1);
    }
    return TRUE;
}