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
struct sbg_script_synth {int vol; int /*<<< orphan*/  type; } ;
struct sbg_parser {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FORWARD_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SBG_TYPE_MIX ; 
 int /*<<< orphan*/  lex_fixed (struct sbg_parser*,char*,int) ; 
 int /*<<< orphan*/  parse_volume (struct sbg_parser*,int*) ; 

__attribute__((used)) static int parse_synth_channel_mix(struct sbg_parser *p,
                                   struct sbg_script_synth *synth)
{
    int vol;

    if (!lex_fixed(p, "mix", 3))
        return 0;
    FORWARD_ERROR(parse_volume(p, &vol));
    synth->type    = SBG_TYPE_MIX;
    synth->vol     = vol;
    return 1;
}