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
typedef  int /*<<< orphan*/  AVStream ;
typedef  int /*<<< orphan*/  AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/ * add_dstream (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  real_parse_asm_rule (int /*<<< orphan*/ *,char const*,char const*) ; 
 char* strchr (char const*,char) ; 

__attribute__((used)) static void
real_parse_asm_rulebook(AVFormatContext *s, AVStream *orig_st,
                        const char *p)
{
    const char *end;
    int n_rules = 0, odd = 0;
    AVStream *st;

    /**
     * The ASMRuleBook contains a list of comma-separated strings per rule,
     * and each rule is separated by a ;. The last one also has a ; at the
     * end so we can use it as delimiter.
     * Every rule occurs twice, once for when the RTSP packet header marker
     * is set and once for if it isn't. We only read the first because we
     * don't care much (that's what the "odd" variable is for).
     * Each rule contains a set of one or more statements, optionally
     * preceded by a single condition. If there's a condition, the rule
     * starts with a '#'. Multiple conditions are merged between brackets,
     * so there are never multiple conditions spread out over separate
     * statements. Generally, these conditions are bitrate limits (min/max)
     * for multi-bitrate streams.
     */
    if (*p == '\"') p++;
    while (1) {
        if (!(end = strchr(p, ';')))
            break;
        if (!odd && end != p) {
            if (n_rules > 0)
                st = add_dstream(s, orig_st);
            else
                st = orig_st;
            if (!st)
                break;
            real_parse_asm_rule(st, p, end);
            n_rules++;
        }
        p = end + 1;
        odd ^= 1;
    }
}