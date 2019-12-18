#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ class; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ bucket ;

/* Variables and functions */
 int EOF ; 
 int L_PAREN ; 
#define  MARK 130 
 int /*<<< orphan*/  NO_SPACE (char*) ; 
#define  START 129 
 scalar_t__ TERM ; 
#define  TEXT 128 
 char* copy_args (int*) ; 
 int /*<<< orphan*/  copy_text () ; 
 char* cptr ; 
 int /*<<< orphan*/  declare_start () ; 
 TYPE_1__* get_name () ; 
 TYPE_1__* goal ; 
 int /*<<< orphan*/  isalpha (int) ; 
 int keyword () ; 
 int /*<<< orphan*/  line ; 
 void* lineno ; 
 int nextc () ; 
 int /*<<< orphan*/  no_grammar () ; 
 int /*<<< orphan*/  parse_arginfo (TYPE_1__*,char*,int) ; 
 void* rescan_lineno ; 
 int /*<<< orphan*/  start_rule (TYPE_1__*,int) ; 
 int /*<<< orphan*/  syntax_error (void*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  terminal_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unexpected_EOF () ; 

__attribute__((used)) static void
advance_to_start(void)
{
    int c;
    bucket *bp;
    char *s_cptr;
    int s_lineno;
#if defined(YYBTYACC)
    char *args = NULL;
    int argslen = 0;
#endif

    for (;;)
    {
	c = nextc();
	if (c != '%')
	    break;
	s_cptr = cptr;
	switch (keyword())
	{
	case MARK:
	    no_grammar();

	case TEXT:
	    copy_text();
	    break;

	case START:
	    declare_start();
	    break;

	default:
	    syntax_error(lineno, line, s_cptr);
	}
    }

    c = nextc();
    if (!isalpha(c) && c != '_' && c != '.' && c != '_')
	syntax_error(lineno, line, cptr);
    bp = get_name();
    if (goal == 0)
    {
	if (bp->class == TERM)
	    terminal_start(bp->name);
	goal = bp;
    }

    s_lineno = lineno;
    c = nextc();
    if (c == EOF)
	unexpected_EOF();
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
    if (c != ':')
	syntax_error(lineno, line, cptr);
    start_rule(bp, s_lineno);
#if defined(YYBTYACC)
    parse_arginfo(bp, args, argslen);
#endif
    ++cptr;
}