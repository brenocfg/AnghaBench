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
struct sbg_parser {int end; int cursor; } ;

/* Variables and functions */
 scalar_t__ memcmp (int,char const*,int) ; 

__attribute__((used)) static int lex_fixed(struct sbg_parser *p, const char *t, int l)
{
    if (p->end - p->cursor < l || memcmp(p->cursor, t, l))
        return 0;
    p->cursor += l;
    return 1;
}