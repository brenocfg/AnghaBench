#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* g; } ;
struct TYPE_4__ {int /*<<< orphan*/  codec_opts; } ;
typedef  TYPE_2__ OptionsContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 char* av_asprintf (char*,char const*) ; 
 int av_dict_set (int /*<<< orphan*/ *,char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_free (char*) ; 
 int /*<<< orphan*/  options ; 
 int parse_option (TYPE_2__*,char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int opt_timecode(void *optctx, const char *opt, const char *arg)
{
    OptionsContext *o = optctx;
    int ret;
    char *tcr = av_asprintf("timecode=%s", arg);
    if (!tcr)
        return AVERROR(ENOMEM);
    ret = parse_option(o, "metadata:g", tcr, options);
    if (ret >= 0)
        ret = av_dict_set(&o->g->codec_opts, "gop_timecode", arg, 0);
    av_free(tcr);
    return ret;
}