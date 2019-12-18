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
struct If {char* form; int formlen; } ;
typedef  enum if_states { ____Placeholder_if_states } if_states ;
typedef  scalar_t__ Boolean ;

/* Variables and functions */
 int COND_INVALID ; 
 int COND_PARSE ; 
 int COND_SKIP ; 
 int Cond_EvalExpression (struct If const*,char*,scalar_t__*,int,scalar_t__) ; 
 scalar_t__ FALSE ; 
 unsigned int MAXIF ; 
 scalar_t__ MAXIF_BUMP ; 
 int PARSE_FATAL ; 
 int PARSE_WARNING ; 
 int /*<<< orphan*/  Parse_Error (int,char*) ; 
 scalar_t__ TRUE ; 
 int* bmake_malloc (unsigned int) ; 
 int* bmake_realloc (int*,unsigned int) ; 
 size_t cond_depth ; 
 size_t cond_min_depth ; 
 struct If* ifs ; 
 scalar_t__ istoken (char*,char*,int) ; 

int
Cond_Eval(char *line)
{
#define	    MAXIF      128	/* maximum depth of .if'ing */
#define	    MAXIF_BUMP  32	/* how much to grow by */
    enum if_states {
	IF_ACTIVE,		/* .if or .elif part active */
	ELSE_ACTIVE,		/* .else part active */
	SEARCH_FOR_ELIF,	/* searching for .elif/else to execute */
	SKIP_TO_ELSE,           /* has been true, but not seen '.else' */
	SKIP_TO_ENDIF		/* nothing else to execute */
    };
    static enum if_states *cond_state = NULL;
    static unsigned int max_if_depth = MAXIF;

    const struct If *ifp;
    Boolean 	    isElif;
    Boolean 	    value;
    int	    	    level;  	/* Level at which to report errors. */
    enum if_states  state;

    level = PARSE_FATAL;
    if (!cond_state) {
	cond_state = bmake_malloc(max_if_depth * sizeof(*cond_state));
	cond_state[0] = IF_ACTIVE;
    }
    /* skip leading character (the '.') and any whitespace */
    for (line++; *line == ' ' || *line == '\t'; line++)
	continue;

    /* Find what type of if we're dealing with.  */
    if (line[0] == 'e') {
	if (line[1] != 'l') {
	    if (!istoken(line + 1, "ndif", 4))
		return COND_INVALID;
	    /* End of conditional section */
	    if (cond_depth == cond_min_depth) {
		Parse_Error(level, "if-less endif");
		return COND_PARSE;
	    }
	    /* Return state for previous conditional */
	    cond_depth--;
	    return cond_state[cond_depth] <= ELSE_ACTIVE ? COND_PARSE : COND_SKIP;
	}

	/* Quite likely this is 'else' or 'elif' */
	line += 2;
	if (istoken(line, "se", 2)) {
	    /* It is else... */
	    if (cond_depth == cond_min_depth) {
		Parse_Error(level, "if-less else");
		return COND_PARSE;
	    }

	    state = cond_state[cond_depth];
	    switch (state) {
	    case SEARCH_FOR_ELIF:
		state = ELSE_ACTIVE;
		break;
	    case ELSE_ACTIVE:
	    case SKIP_TO_ENDIF:
		Parse_Error(PARSE_WARNING, "extra else");
		/* FALLTHROUGH */
	    default:
	    case IF_ACTIVE:
	    case SKIP_TO_ELSE:
		state = SKIP_TO_ENDIF;
		break;
	    }
	    cond_state[cond_depth] = state;
	    return state <= ELSE_ACTIVE ? COND_PARSE : COND_SKIP;
	}
	/* Assume for now it is an elif */
	isElif = TRUE;
    } else
	isElif = FALSE;

    if (line[0] != 'i' || line[1] != 'f')
	/* Not an ifxxx or elifxxx line */
	return COND_INVALID;

    /*
     * Figure out what sort of conditional it is -- what its default
     * function is, etc. -- by looking in the table of valid "ifs"
     */
    line += 2;
    for (ifp = ifs; ; ifp++) {
	if (ifp->form == NULL)
	    return COND_INVALID;
	if (istoken(ifp->form, line, ifp->formlen)) {
	    line += ifp->formlen;
	    break;
	}
    }

    /* Now we know what sort of 'if' it is... */

    if (isElif) {
	if (cond_depth == cond_min_depth) {
	    Parse_Error(level, "if-less elif");
	    return COND_PARSE;
	}
	state = cond_state[cond_depth];
	if (state == SKIP_TO_ENDIF || state == ELSE_ACTIVE) {
	    Parse_Error(PARSE_WARNING, "extra elif");
	    cond_state[cond_depth] = SKIP_TO_ENDIF;
	    return COND_SKIP;
	}
	if (state != SEARCH_FOR_ELIF) {
	    /* Either just finished the 'true' block, or already SKIP_TO_ELSE */
	    cond_state[cond_depth] = SKIP_TO_ELSE;
	    return COND_SKIP;
	}
    } else {
	/* Normal .if */
	if (cond_depth + 1 >= max_if_depth) {
	    /*
	     * This is rare, but not impossible.
	     * In meta mode, dirdeps.mk (only runs at level 0)
	     * can need more than the default.
	     */
	    max_if_depth += MAXIF_BUMP;
	    cond_state = bmake_realloc(cond_state, max_if_depth *
		sizeof(*cond_state));
	}
	state = cond_state[cond_depth];
	cond_depth++;
	if (state > ELSE_ACTIVE) {
	    /* If we aren't parsing the data, treat as always false */
	    cond_state[cond_depth] = SKIP_TO_ELSE;
	    return COND_SKIP;
	}
    }

    /* And evaluate the conditional expresssion */
    if (Cond_EvalExpression(ifp, line, &value, 1, TRUE) == COND_INVALID) {
	/* Syntax error in conditional, error message already output. */
	/* Skip everything to matching .endif */
	cond_state[cond_depth] = SKIP_TO_ELSE;
	return COND_SKIP;
    }

    if (!value) {
	cond_state[cond_depth] = SEARCH_FOR_ELIF;
	return COND_SKIP;
    }
    cond_state[cond_depth] = IF_ACTIVE;
    return COND_PARSE;
}