#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int args; scalar_t__* argtags; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ bucket ;
struct TYPE_9__ {int args; scalar_t__* argtags; } ;

/* Variables and functions */
 int L_PAREN ; 
 int /*<<< orphan*/  NO_SPACE (char*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int can_elide_arg (char**,scalar_t__) ; 
 char* copy_args (int*) ; 
 int* cptr ; 
 int /*<<< orphan*/  end_rule () ; 
 int /*<<< orphan*/  expand_items () ; 
 int /*<<< orphan*/  free (char*) ; 
 TYPE_1__* get_literal () ; 
 TYPE_1__* get_name () ; 
 char* insert_arg_rule (char*,scalar_t__) ; 
 int /*<<< orphan*/  insert_empty_rule () ; 
 scalar_t__ last_was_action ; 
 void* lineno ; 
 int maxitems ; 
 int nextc () ; 
 int nitems ; 
 size_t nrules ; 
 int /*<<< orphan*/  parse_arginfo (TYPE_1__*,char*,int) ; 
 TYPE_1__** pitem ; 
 TYPE_3__** plhs ; 
 void* rescan_lineno ; 
 int /*<<< orphan*/  start_rule (TYPE_1__*,int) ; 
 int /*<<< orphan*/  wrong_number_args_warning (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrong_type_for_arg_warning (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
add_symbol(void)
{
    int c;
    bucket *bp;
    int s_lineno = lineno;
#if defined(YYBTYACC)
    char *args = NULL;
    int argslen = 0;
#endif

    c = *cptr;
    if (c == '\'' || c == '"')
	bp = get_literal();
    else
	bp = get_name();

    c = nextc();
    rescan_lineno = lineno;	/* line# for possible inherited args rescan */
#if defined(YYBTYACC)
    if (c == L_PAREN)
    {
	++cptr;
	args = copy_args(&argslen);
	NO_SPACE(args);
	c = nextc();
    }
#endif
    if (c == ':')
    {
	end_rule();
	start_rule(bp, s_lineno);
#if defined(YYBTYACC)
	parse_arginfo(bp, args, argslen);
#endif
	++cptr;
	return;
    }

    if (last_was_action)
	insert_empty_rule();
    last_was_action = 0;

#if defined(YYBTYACC)
    if (bp->args < 0)
	bp->args = argslen;
    if (argslen == 0 && bp->args > 0 && pitem[nitems - 1] == NULL)
    {
	int i;
	if (plhs[nrules]->args != bp->args)
	    wrong_number_args_warning("default ", bp->name);
	for (i = bp->args - 1; i >= 0; i--)
	    if (plhs[nrules]->argtags[i] != bp->argtags[i])
		wrong_type_for_arg_warning(i + 1, bp->name);
    }
    else if (bp->args != argslen)
	wrong_number_args_warning("", bp->name);
    if (args != 0)
    {
	char *ap = args;
	int i = 0;
	int elide_cnt = can_elide_arg(&ap, bp->argtags[0]);

	if (elide_cnt > argslen)
	    elide_cnt = 0;
	if (elide_cnt)
	{
	    for (i = 1; i < elide_cnt; i++)
		if (can_elide_arg(&ap, bp->argtags[i]) != elide_cnt - i)
		{
		    elide_cnt = 0;
		    break;
		}
	}
	if (elide_cnt)
	{
	    assert(i == elide_cnt);
	}
	else
	{
	    ap = args;
	    i = 0;
	}
	for (; i < argslen; i++)
	    ap = insert_arg_rule(ap, bp->argtags[i]);
	free(args);
    }
#endif /* defined(YYBTYACC) */

    if (++nitems > maxitems)
	expand_items();
    pitem[nitems - 1] = bp;
}