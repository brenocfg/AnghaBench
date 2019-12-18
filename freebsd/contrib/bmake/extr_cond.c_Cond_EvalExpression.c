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
struct If {scalar_t__* form; } ;
typedef  int /*<<< orphan*/  Token ;
typedef  int /*<<< orphan*/  Boolean ;

/* Variables and functions */
 int COND_INVALID ; 
 int /*<<< orphan*/  PARSE_FATAL ; 
 int /*<<< orphan*/  Parse_Error (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  TOK_NONE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 char* condExpr ; 
 int /*<<< orphan*/  condPushBack ; 
 int do_Cond_EvalExpression (int /*<<< orphan*/ *) ; 
 struct If const* if_info ; 
 struct If* ifs ; 
 int /*<<< orphan*/  lhsStrict ; 

int
Cond_EvalExpression(const struct If *info, char *line, Boolean *value, int eprint, Boolean strictLHS)
{
    static const struct If *dflt_info;
    const struct If *sv_if_info = if_info;
    char *sv_condExpr = condExpr;
    Token sv_condPushBack = condPushBack;
    int rval;

    lhsStrict = strictLHS;

    while (*line == ' ' || *line == '\t')
	line++;

    if (info == NULL && (info = dflt_info) == NULL) {
	/* Scan for the entry for .if - it can't be first */
	for (info = ifs; ; info++)
	    if (info->form[0] == 0)
		break;
	dflt_info = info;
    }
    assert(info != NULL);

    if_info = info;
    condExpr = line;
    condPushBack = TOK_NONE;

    rval = do_Cond_EvalExpression(value);

    if (rval == COND_INVALID && eprint)
	Parse_Error(PARSE_FATAL, "Malformed conditional (%s)", line);

    if_info = sv_if_info;
    condExpr = sv_condExpr;
    condPushBack = sv_condPushBack;

    return rval;
}