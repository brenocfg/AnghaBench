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
struct sbg_string {char* s; char* e; } ;
struct sbg_parser {char* cursor; char* end; } ;

/* Variables and functions */
 int /*<<< orphan*/  is_space (char) ; 
 int /*<<< orphan*/  lex_space (struct sbg_parser*) ; 

__attribute__((used)) static int lex_wsword(struct sbg_parser *p, struct sbg_string *rs)
{
    char *s = p->cursor, *c = s;

    if (s == p->end || *s == '\n')
        return 0;
    while (c < p->end && *c != '\n' && !is_space(*c))
        c++;
    rs->s = s;
    rs->e = p->cursor = c;
    lex_space(p);
    return 1;
}