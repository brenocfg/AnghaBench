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
struct sbg_parser {int cursor; } ;
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 int str_to_time (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lex_time(struct sbg_parser *p, int64_t *rt)
{
    int r = str_to_time(p->cursor, rt);
    p->cursor += r;
    return r > 0;
}