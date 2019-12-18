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
struct sbg_parser {char* cursor; char* end; } ;

/* Variables and functions */
 scalar_t__ is_space (char) ; 

__attribute__((used)) static int lex_space(struct sbg_parser *p)
{
    char *c = p->cursor;

    while (p->cursor < p->end && is_space(*p->cursor))
        p->cursor++;
    return p->cursor > c;
}