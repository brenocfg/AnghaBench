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
struct TYPE_4__ {int /*<<< orphan*/  name; int /*<<< orphan*/  config_props; int /*<<< orphan*/  type; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ AVFilterPad ;
typedef  int /*<<< orphan*/  AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AVMEDIA_TYPE_AUDIO ; 
 int /*<<< orphan*/  AVMEDIA_TYPE_VIDEO ; 
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_asprintf (char*,char const*,int) ; 
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  config_output ; 
 int ff_insert_inpad (int /*<<< orphan*/ *,int,TYPE_1__*) ; 
 int ff_insert_outpad (int /*<<< orphan*/ *,int,TYPE_1__*) ; 

__attribute__((used)) static int parse_definition(AVFilterContext *ctx, int nb_pads, int is_input, int is_audio)
{
    const char *padtype = is_input ? "in" : "out";
    int i = 0, ret = 0;

    for (i = 0; i < nb_pads; i++) {
        AVFilterPad pad = { 0 };

        pad.type = is_audio ? AVMEDIA_TYPE_AUDIO : AVMEDIA_TYPE_VIDEO;

        pad.name = av_asprintf("%sput%d", padtype, i);
        if (!pad.name)
            return AVERROR(ENOMEM);

        av_log(ctx, AV_LOG_DEBUG, "Add %s pad %s\n", padtype, pad.name);

        if (is_input) {
            ret = ff_insert_inpad(ctx, i, &pad);
        } else {
            pad.config_props  = config_output;
            ret = ff_insert_outpad(ctx, i, &pad);
        }

        if (ret < 0) {
            av_freep(&pad.name);
            return ret;
        }
    }

    return 0;
}