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
struct sbg_script_synth {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  nb_synth; int /*<<< orphan*/  synth; } ;
struct sbg_parser {TYPE_1__ scs; int /*<<< orphan*/  nb_synth_max; } ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct sbg_script_synth* alloc_array_elem (void**,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int lex_char (struct sbg_parser*,char) ; 
 int parse_synth_channel_bell (struct sbg_parser*,struct sbg_script_synth*) ; 
 int parse_synth_channel_mix (struct sbg_parser*,struct sbg_script_synth*) ; 
 int parse_synth_channel_pink (struct sbg_parser*,struct sbg_script_synth*) ; 
 int parse_synth_channel_sine (struct sbg_parser*,struct sbg_script_synth*) ; 
 int parse_synth_channel_spin (struct sbg_parser*,struct sbg_script_synth*) ; 

__attribute__((used)) static int parse_synth_channel(struct sbg_parser *p)
{
    int r;
    struct sbg_script_synth *synth;

    synth = alloc_array_elem((void **)&p->scs.synth, sizeof(*synth),
                             &p->scs.nb_synth, &p->nb_synth_max);
    if (!synth)
        return AVERROR(ENOMEM);
    r = lex_char(p, '-');
    if (!r)
        r = parse_synth_channel_pink(p, synth);
    if (!r)
        r = parse_synth_channel_bell(p, synth);
    if (!r)
        r = parse_synth_channel_mix(p, synth);
    if (!r)
        r = parse_synth_channel_spin(p, synth);
    /* Unimplemented: wave%d:%f%f/vol (carrier, beat) */
    if (!r)
        r = parse_synth_channel_sine(p, synth);
    if (r <= 0)
        p->scs.nb_synth--;
    return r;
}