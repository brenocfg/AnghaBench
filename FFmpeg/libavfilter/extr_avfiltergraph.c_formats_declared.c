#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int nb_inputs; int nb_outputs; TYPE_2__** outputs; TYPE_1__** inputs; } ;
struct TYPE_6__ {scalar_t__ type; scalar_t__ in_channel_layouts; scalar_t__ in_samplerates; int /*<<< orphan*/  in_formats; } ;
struct TYPE_5__ {scalar_t__ type; scalar_t__ out_channel_layouts; scalar_t__ out_samplerates; int /*<<< orphan*/  out_formats; } ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */
 scalar_t__ AVMEDIA_TYPE_AUDIO ; 

__attribute__((used)) static int formats_declared(AVFilterContext *f)
{
    int i;

    for (i = 0; i < f->nb_inputs; i++) {
        if (!f->inputs[i]->out_formats)
            return 0;
        if (f->inputs[i]->type == AVMEDIA_TYPE_AUDIO &&
            !(f->inputs[i]->out_samplerates &&
              f->inputs[i]->out_channel_layouts))
            return 0;
    }
    for (i = 0; i < f->nb_outputs; i++) {
        if (!f->outputs[i]->in_formats)
            return 0;
        if (f->outputs[i]->type == AVMEDIA_TYPE_AUDIO &&
            !(f->outputs[i]->in_samplerates &&
              f->outputs[i]->in_channel_layouts))
            return 0;
    }
    return 1;
}