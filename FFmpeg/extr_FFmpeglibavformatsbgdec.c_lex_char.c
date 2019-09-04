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

__attribute__((used)) static int lex_char(struct sbg_parser *p, char c)
{
    int r = p->cursor < p->end && *p->cursor == c;

    p->cursor += r;
    return r;
}