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
typedef  scalar_t__ Boolean ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ ISEQOPERATOR (char) ; 
 scalar_t__ TRUE ; 
 scalar_t__ strncmp (char*,char*,int) ; 

Boolean
Parse_IsVar(char *line)
{
    Boolean wasSpace = FALSE;	/* set TRUE if found a space */
    char ch;
    int level = 0;
#define ISEQOPERATOR(c) \
	(((c) == '+') || ((c) == ':') || ((c) == '?') || ((c) == '!'))

    /*
     * Skip to variable name
     */
    for (;(*line == ' ') || (*line == '\t'); line++)
	continue;

    /* Scan for one of the assignment operators outside a variable expansion */
    while ((ch = *line++) != 0) {
	if (ch == '(' || ch == '{') {
	    level++;
	    continue;
	}
	if (ch == ')' || ch == '}') {
	    level--;
	    continue;
	}
	if (level != 0)
	    continue;
	while (ch == ' ' || ch == '\t') {
	    ch = *line++;
	    wasSpace = TRUE;
	}
#ifdef SUNSHCMD
	if (ch == ':' && strncmp(line, "sh", 2) == 0) {
	    line += 2;
	    continue;
	}
#endif
	if (ch == '=')
	    return TRUE;
	if (*line == '=' && ISEQOPERATOR(ch))
	    return TRUE;
	if (wasSpace)
	    return FALSE;
    }

    return FALSE;
}