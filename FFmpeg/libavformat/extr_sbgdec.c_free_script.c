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
struct sbg_script {int /*<<< orphan*/  opt_mix; int /*<<< orphan*/  events; int /*<<< orphan*/  block_tseq; int /*<<< orphan*/  tseq; int /*<<< orphan*/  synth; int /*<<< orphan*/  def; } ;

/* Variables and functions */
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void free_script(struct sbg_script *s)
{
    av_freep(&s->def);
    av_freep(&s->synth);
    av_freep(&s->tseq);
    av_freep(&s->block_tseq);
    av_freep(&s->events);
    av_freep(&s->opt_mix);
}