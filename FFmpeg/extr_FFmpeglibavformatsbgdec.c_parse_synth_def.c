#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sbg_script_definition {char type; int elements; int nb_elements; } ;
struct TYPE_2__ {int nb_synth; } ;
struct sbg_parser {TYPE_1__ scs; } ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  lex_line_end (struct sbg_parser*) ; 
 int /*<<< orphan*/  lex_space (struct sbg_parser*) ; 
 int parse_synth_channel (struct sbg_parser*) ; 

__attribute__((used)) static int parse_synth_def(struct sbg_parser *p,
                           struct sbg_script_definition *def)
{
    int r, synth;

    synth = p->scs.nb_synth;
    while (1) {
        r = parse_synth_channel(p);
        if (r < 0)
            return r;
        if (!r || !lex_space(p))
            break;
    }
    lex_space(p);
    if (synth == p->scs.nb_synth)
        return AVERROR_INVALIDDATA;
    if (!lex_line_end(p))
        return AVERROR_INVALIDDATA;
    def->type        = 'S';
    def->elements    = synth;
    def->nb_elements = p->scs.nb_synth - synth;
    return 1;
}