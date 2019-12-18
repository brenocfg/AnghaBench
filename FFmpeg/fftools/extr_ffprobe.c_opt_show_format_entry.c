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
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  ENOMEM ; 
 char* av_asprintf (char*,char const*) ; 
 int /*<<< orphan*/  av_free (char*) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char const*,char const*) ; 
 int opt_show_entries (void*,char const*,char*) ; 

__attribute__((used)) static int opt_show_format_entry(void *optctx, const char *opt, const char *arg)
{
    char *buf = av_asprintf("format=%s", arg);
    int ret;

    if (!buf)
        return AVERROR(ENOMEM);

    av_log(NULL, AV_LOG_WARNING,
           "Option '%s' is deprecated, use '-show_entries format=%s' instead\n",
           opt, arg);
    ret = opt_show_entries(optctx, opt, buf);
    av_free(buf);
    return ret;
}