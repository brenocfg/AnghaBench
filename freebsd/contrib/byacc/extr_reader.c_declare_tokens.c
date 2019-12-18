#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char* tag; scalar_t__ prec; scalar_t__ value; int /*<<< orphan*/  name; scalar_t__ assoc; int /*<<< orphan*/  class; } ;
typedef  TYPE_1__ bucket ;
typedef  scalar_t__ Value_t ;
typedef  scalar_t__ Assoc_t ;

/* Variables and functions */
 int EOF ; 
 int /*<<< orphan*/  TERM ; 
 int TOKEN ; 
 scalar_t__ UNDEFINED ; 
 TYPE_1__* get_literal () ; 
 TYPE_1__* get_name () ; 
 scalar_t__ get_number () ; 
 char* get_tag () ; 
 TYPE_1__* goal ; 
 scalar_t__ isalpha (int) ; 
 scalar_t__ isdigit (int) ; 
 int nextc () ; 
 scalar_t__ prec ; 
 int /*<<< orphan*/  reprec_warning (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  retyped_warning (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  revalued_warning (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tokenized_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unexpected_EOF () ; 

__attribute__((used)) static void
declare_tokens(int assoc)
{
    int c;
    bucket *bp;
    Value_t value;
    char *tag = 0;

    if (assoc != TOKEN)
	++prec;

    c = nextc();
    if (c == EOF)
	unexpected_EOF();
    if (c == '<')
    {
	tag = get_tag();
	c = nextc();
	if (c == EOF)
	    unexpected_EOF();
    }

    for (;;)
    {
	if (isalpha(c) || c == '_' || c == '.' || c == '$')
	    bp = get_name();
	else if (c == '\'' || c == '"')
	    bp = get_literal();
	else
	    return;

	if (bp == goal)
	    tokenized_start(bp->name);
	bp->class = TERM;

	if (tag)
	{
	    if (bp->tag && tag != bp->tag)
		retyped_warning(bp->name);
	    bp->tag = tag;
	}

	if (assoc != TOKEN)
	{
	    if (bp->prec && prec != bp->prec)
		reprec_warning(bp->name);
	    bp->assoc = (Assoc_t)assoc;
	    bp->prec = prec;
	}

	c = nextc();
	if (c == EOF)
	    unexpected_EOF();

	value = UNDEFINED;
	if (isdigit(c))
	{
	    value = get_number();
	    if (bp->value != UNDEFINED && value != bp->value)
		revalued_warning(bp->name);
	    bp->value = value;
	    c = nextc();
	    if (c == EOF)
		unexpected_EOF();
	}
    }
}