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
struct sbg_timestamp {char type; scalar_t__ t; } ;
struct sbg_parser {int dummy; } ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 scalar_t__ lex_char (struct sbg_parser*,char) ; 
 scalar_t__ lex_fixed (struct sbg_parser*,char*,int) ; 
 int /*<<< orphan*/  lex_space (struct sbg_parser*) ; 
 int lex_time (struct sbg_parser*,scalar_t__*) ; 

__attribute__((used)) static int parse_timestamp(struct sbg_parser *p,
                               struct sbg_timestamp *rts, int64_t *rrel)
{
    int64_t abs = 0, rel = 0, dt;
    char type = 0;
    int r;

    if (lex_fixed(p, "NOW", 3)) {
        type = 'N';
        r = 1;
    } else {
        r = lex_time(p, &abs);
        if (r)
            type = 'T';
    }
    while (lex_char(p, '+')) {
        if (!lex_time(p, &dt))
            return AVERROR_INVALIDDATA;
        rel += dt;
        r = 1;
    }
    if (r) {
        if (!lex_space(p))
            return AVERROR_INVALIDDATA;
        rts->type = type;
        rts->t    = abs;
        *rrel     = rel;
    }
    return r;
}