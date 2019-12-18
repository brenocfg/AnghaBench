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

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_freep (char**) ; 
 int /*<<< orphan*/  av_log_set_callback (int /*<<< orphan*/ ) ; 
 char* av_strdup (char const*) ; 
 int /*<<< orphan*/  log_callback_help ; 
 int /*<<< orphan*/  show_help_bsf (char*) ; 
 int /*<<< orphan*/  show_help_codec (char*,int) ; 
 int /*<<< orphan*/  show_help_default (char*,char*) ; 
 int /*<<< orphan*/  show_help_demuxer (char*) ; 
 int /*<<< orphan*/  show_help_filter (char*) ; 
 int /*<<< orphan*/  show_help_muxer (char*) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

int show_help(void *optctx, const char *opt, const char *arg)
{
    char *topic, *par;
    av_log_set_callback(log_callback_help);

    topic = av_strdup(arg ? arg : "");
    if (!topic)
        return AVERROR(ENOMEM);
    par = strchr(topic, '=');
    if (par)
        *par++ = 0;

    if (!*topic) {
        show_help_default(topic, par);
    } else if (!strcmp(topic, "decoder")) {
        show_help_codec(par, 0);
    } else if (!strcmp(topic, "encoder")) {
        show_help_codec(par, 1);
    } else if (!strcmp(topic, "demuxer")) {
        show_help_demuxer(par);
    } else if (!strcmp(topic, "muxer")) {
        show_help_muxer(par);
#if CONFIG_AVFILTER
    } else if (!strcmp(topic, "filter")) {
        show_help_filter(par);
#endif
    } else if (!strcmp(topic, "bsf")) {
        show_help_bsf(par);
    } else {
        show_help_default(topic, par);
    }

    av_freep(&topic);
    return 0;
}