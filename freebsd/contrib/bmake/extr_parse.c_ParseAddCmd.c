#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int type; int /*<<< orphan*/  name; int /*<<< orphan*/  lineno; int /*<<< orphan*/  fname; int /*<<< orphan*/  commands; int /*<<< orphan*/  cohorts; } ;
typedef  TYPE_1__ GNode ;

/* Variables and functions */
 int /*<<< orphan*/  Lst_AtEnd (int /*<<< orphan*/ ,void*) ; 
 scalar_t__ Lst_Datum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Lst_IsEmpty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Lst_Last (int /*<<< orphan*/ ) ; 
 int OP_DOUBLEDEP ; 
 int OP_HAS_COMMANDS ; 
 int OP_SUBMAKE ; 
 int /*<<< orphan*/  PARSE_WARNING ; 
 int /*<<< orphan*/  ParseErrorInternal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ParseMark (TYPE_1__*) ; 
 scalar_t__ ParseMaybeSubMake (void*) ; 
 int /*<<< orphan*/  Parse_Error (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static int
ParseAddCmd(void *gnp, void *cmd)
{
    GNode *gn = (GNode *)gnp;

    /* Add to last (ie current) cohort for :: targets */
    if ((gn->type & OP_DOUBLEDEP) && !Lst_IsEmpty (gn->cohorts))
	gn = (GNode *)Lst_Datum(Lst_Last(gn->cohorts));

    /* if target already supplied, ignore commands */
    if (!(gn->type & OP_HAS_COMMANDS)) {
	(void)Lst_AtEnd(gn->commands, cmd);
	if (ParseMaybeSubMake(cmd))
	    gn->type |= OP_SUBMAKE;
	ParseMark(gn);
    } else {
#ifdef notyet
	/* XXX: We cannot do this until we fix the tree */
	(void)Lst_AtEnd(gn->commands, cmd);
	Parse_Error(PARSE_WARNING,
		     "overriding commands for target \"%s\"; "
		     "previous commands defined at %s: %d ignored",
		     gn->name, gn->fname, gn->lineno);
#else
	Parse_Error(PARSE_WARNING,
		     "duplicate script for target \"%s\" ignored",
		     gn->name);
	ParseErrorInternal(gn->fname, gn->lineno, PARSE_WARNING,
			    "using previous script for \"%s\" defined here",
			    gn->name);
#endif
    }
    return(0);
}