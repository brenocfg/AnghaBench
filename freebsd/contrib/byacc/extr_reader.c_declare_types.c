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
struct TYPE_5__ {char* tag; int /*<<< orphan*/  name; scalar_t__ args; } ;
typedef  TYPE_1__ bucket ;

/* Variables and functions */
 int EOF ; 
 int L_PAREN ; 
 int /*<<< orphan*/  declare_argtypes (TYPE_1__*) ; 
 TYPE_1__* get_literal () ; 
 TYPE_1__* get_name () ; 
 char* get_tag () ; 
 scalar_t__ isalpha (int) ; 
 int nextc () ; 
 int /*<<< orphan*/  retyped_warning (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unexpected_EOF () ; 

__attribute__((used)) static void
declare_types(void)
{
    int c;
    bucket *bp = NULL;
    char *tag = NULL;

    c = nextc();
    if (c == EOF)
	unexpected_EOF();
    if (c == '<')
	tag = get_tag();

    for (;;)
    {
	c = nextc();
	if (c == EOF)
	    unexpected_EOF();
	if (isalpha(c) || c == '_' || c == '.' || c == '$')
	{
	    bp = get_name();
#if defined(YYBTYACC)
	    if (nextc() == L_PAREN)
		declare_argtypes(bp);
	    else
		bp->args = 0;
#endif
	}
	else if (c == '\'' || c == '"')
	{
	    bp = get_literal();
#if defined(YYBTYACC)
	    bp->args = 0;
#endif
	}
	else
	    return;

	if (tag)
	{
	    if (bp->tag && tag != bp->tag)
		retyped_warning(bp->name);
	    bp->tag = tag;
	}
    }
}