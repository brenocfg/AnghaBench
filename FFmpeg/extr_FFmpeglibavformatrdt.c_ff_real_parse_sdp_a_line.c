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
struct TYPE_4__ {int /*<<< orphan*/ * streams; } ;
typedef  TYPE_1__ AVFormatContext ;

/* Variables and functions */
 scalar_t__ av_strstart (char const*,char*,char const**) ; 
 int /*<<< orphan*/  real_parse_asm_rulebook (TYPE_1__*,int /*<<< orphan*/ ,char const*) ; 

void
ff_real_parse_sdp_a_line (AVFormatContext *s, int stream_index,
                          const char *line)
{
    const char *p = line;

    if (av_strstart(p, "ASMRuleBook:string;", &p))
        real_parse_asm_rulebook(s, s->streams[stream_index], p);
}