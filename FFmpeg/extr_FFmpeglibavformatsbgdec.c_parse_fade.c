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
struct sbg_parser {int dummy; } ;
struct sbg_fade {void* out; void* in; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 void* SBG_FADE_ADAPT ; 
 void* SBG_FADE_SAME ; 
 void* SBG_FADE_SILENCE ; 
 scalar_t__ lex_char (struct sbg_parser*,char) ; 

__attribute__((used)) static int parse_fade(struct sbg_parser *p, struct sbg_fade *fr)
{
    struct sbg_fade f = {0};

    if (lex_char(p, '<'))
        f.in = SBG_FADE_SILENCE;
    else if (lex_char(p, '-'))
        f.in = SBG_FADE_SAME;
    else if (lex_char(p, '='))
        f.in = SBG_FADE_ADAPT;
    else
        return 0;
    if (lex_char(p, '>'))
        f.out = SBG_FADE_SILENCE;
    else if (lex_char(p, '-'))
        f.out = SBG_FADE_SAME;
    else if (lex_char(p, '='))
        f.out = SBG_FADE_ADAPT;
    else
        return AVERROR_INVALIDDATA;
    *fr = f;
    return 1;
}