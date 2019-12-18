#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ class; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ bucket ;

/* Variables and functions */
 int EOF ; 
 scalar_t__ TERM ; 
 int /*<<< orphan*/  cptr ; 
 TYPE_1__* get_name () ; 
 TYPE_1__* goal ; 
 int /*<<< orphan*/  isalpha (int) ; 
 int /*<<< orphan*/  line ; 
 int /*<<< orphan*/  lineno ; 
 int nextc () ; 
 int /*<<< orphan*/  restarted_warning () ; 
 int /*<<< orphan*/  syntax_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  terminal_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unexpected_EOF () ; 

__attribute__((used)) static void
declare_start(void)
{
    int c;
    bucket *bp;

    c = nextc();
    if (c == EOF)
	unexpected_EOF();
    if (!isalpha(c) && c != '_' && c != '.' && c != '$')
	syntax_error(lineno, line, cptr);
    bp = get_name();
    if (bp->class == TERM)
	terminal_start(bp->name);
    if (goal && goal != bp)
	restarted_warning();
    goal = bp;
}