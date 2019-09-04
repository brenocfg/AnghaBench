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
 int /*<<< orphan*/  AV_LOG_FATAL ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  av_find_input_format (char const*) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  file_iformat ; 

__attribute__((used)) static int opt_format(void *optctx, const char *opt, const char *arg)
{
    file_iformat = av_find_input_format(arg);
    if (!file_iformat) {
        av_log(NULL, AV_LOG_FATAL, "Unknown input format: %s\n", arg);
        return AVERROR(EINVAL);
    }
    return 0;
}