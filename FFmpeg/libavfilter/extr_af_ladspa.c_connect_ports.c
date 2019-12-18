#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  (* activate ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* connect_port ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* instantiate ) (TYPE_4__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_10__ {TYPE_1__* priv; } ;
struct TYPE_9__ {int channels; int /*<<< orphan*/  sample_rate; } ;
struct TYPE_8__ {int nb_handles; int nb_inputs; int nb_outputs; int nb_inputcontrols; int nb_outputcontrols; int /*<<< orphan*/ * handles; TYPE_4__* desc; int /*<<< orphan*/ * octlv; int /*<<< orphan*/ * ocmap; int /*<<< orphan*/ * ictlv; int /*<<< orphan*/ * icmap; } ;
typedef  TYPE_1__ LADSPAContext ;
typedef  TYPE_2__ AVFilterLink ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EXTERNAL ; 
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/ * av_calloc (int,int) ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int connect_ports(AVFilterContext *ctx, AVFilterLink *link)
{
    LADSPAContext *s = ctx->priv;
    int i, j;

    s->nb_handles = s->nb_inputs == 1 && s->nb_outputs == 1 ? link->channels : 1;
    s->handles    = av_calloc(s->nb_handles, sizeof(*s->handles));
    if (!s->handles)
        return AVERROR(ENOMEM);

    for (i = 0; i < s->nb_handles; i++) {
        s->handles[i] = s->desc->instantiate(s->desc, link->sample_rate);
        if (!s->handles[i]) {
            av_log(ctx, AV_LOG_ERROR, "Could not instantiate plugin.\n");
            return AVERROR_EXTERNAL;
        }

        // Connect the input control ports
        for (j = 0; j < s->nb_inputcontrols; j++)
            s->desc->connect_port(s->handles[i], s->icmap[j], s->ictlv + j);

        // Connect the output control ports
        for (j = 0; j < s->nb_outputcontrols; j++)
            s->desc->connect_port(s->handles[i], s->ocmap[j], &s->octlv[j]);

        if (s->desc->activate)
            s->desc->activate(s->handles[i]);
    }

    av_log(ctx, AV_LOG_DEBUG, "handles: %d\n", s->nb_handles);

    return 0;
}