#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_8__ {TYPE_2__* priv; } ;
struct TYPE_7__ {TYPE_1__* vspkrpos; int /*<<< orphan*/  speakers_pos; } ;
struct TYPE_6__ {int set; float azim; float elev; } ;
typedef  TYPE_2__ SOFAlizerContext ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  av_free (char*) ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*,char*) ; 
 int av_sscanf (char*,char*,float*,...) ; 
 char* av_strdup (int /*<<< orphan*/ ) ; 
 char* av_strtok (char*,char*,char**) ; 
 scalar_t__ parse_channel_name (char**,int*,char*) ; 

__attribute__((used)) static void parse_speaker_pos(AVFilterContext *ctx, int64_t in_channel_layout)
{
    SOFAlizerContext *s = ctx->priv;
    char *arg, *tokenizer, *p, *args = av_strdup(s->speakers_pos);

    if (!args)
        return;
    p = args;

    while ((arg = av_strtok(p, "|", &tokenizer))) {
        char buf[8];
        float azim, elev;
        int out_ch_id;

        p = NULL;
        if (parse_channel_name(&arg, &out_ch_id, buf)) {
            av_log(ctx, AV_LOG_WARNING, "Failed to parse \'%s\' as channel name.\n", buf);
            continue;
        }
        if (av_sscanf(arg, "%f %f", &azim, &elev) == 2) {
            s->vspkrpos[out_ch_id].set = 1;
            s->vspkrpos[out_ch_id].azim = azim;
            s->vspkrpos[out_ch_id].elev = elev;
        } else if (av_sscanf(arg, "%f", &azim) == 1) {
            s->vspkrpos[out_ch_id].set = 1;
            s->vspkrpos[out_ch_id].azim = azim;
            s->vspkrpos[out_ch_id].elev = 0;
        }
    }

    av_free(args);
}