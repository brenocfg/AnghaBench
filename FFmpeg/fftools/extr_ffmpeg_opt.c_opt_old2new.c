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
typedef  int /*<<< orphan*/  OptionsContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 char* av_asprintf (char*,char const*,char const) ; 
 int /*<<< orphan*/  av_free (char*) ; 
 int /*<<< orphan*/  options ; 
 int parse_option (int /*<<< orphan*/ *,char*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int opt_old2new(void *optctx, const char *opt, const char *arg)
{
    OptionsContext *o = optctx;
    int ret;
    char *s = av_asprintf("%s:%c", opt + 1, *opt);
    if (!s)
        return AVERROR(ENOMEM);
    ret = parse_option(o, s, arg, options);
    av_free(s);
    return ret;
}