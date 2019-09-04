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
struct TYPE_4__ {int /*<<< orphan*/  scale_sws_opts; } ;
typedef  TYPE_1__ AVFilterGraph ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_log (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  av_mallocz (int) ; 
 int /*<<< orphan*/  av_strlcpy (int /*<<< orphan*/ ,char const*,int) ; 
 char* strchr (char const*,char) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 

__attribute__((used)) static int parse_sws_flags(const char **buf, AVFilterGraph *graph)
{
    char *p = strchr(*buf, ';');

    if (strncmp(*buf, "sws_flags=", 10))
        return 0;

    if (!p) {
        av_log(graph, AV_LOG_ERROR, "sws_flags not terminated with ';'.\n");
        return AVERROR(EINVAL);
    }

    *buf += 4;  // keep the 'flags=' part

    av_freep(&graph->scale_sws_opts);
    if (!(graph->scale_sws_opts = av_mallocz(p - *buf + 1)))
        return AVERROR(ENOMEM);
    av_strlcpy(graph->scale_sws_opts, *buf, p - *buf + 1);

    *buf = p + 1;
    return 0;
}