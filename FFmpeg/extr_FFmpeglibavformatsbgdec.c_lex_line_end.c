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
struct sbg_parser {char* cursor; char* end; int /*<<< orphan*/  line_no; } ;

/* Variables and functions */
 int /*<<< orphan*/  lex_space (struct sbg_parser*) ; 

__attribute__((used)) static int lex_line_end(struct sbg_parser *p)
{
    if (p->cursor < p->end && *p->cursor == '#') {
        p->cursor++;
        while (p->cursor < p->end && *p->cursor != '\n')
            p->cursor++;
    }
    if (p->cursor == p->end)
        /* simulate final LF for files lacking it */
        return 1;
    if (*p->cursor != '\n')
        return 0;
    p->cursor++;
    p->line_no++;
    lex_space(p);
    return 1;
}