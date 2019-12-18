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
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char const*,char const*) ; 

__attribute__((used)) static int opt_sameq(void *optctx, const char *opt, const char *arg)
{
    av_log(NULL, AV_LOG_ERROR, "Option '%s' was removed. "
           "If you are looking for an option to preserve the quality (which is not "
           "what -%s was for), use -qscale 0 or an equivalent quality factor option.\n",
           opt, opt);
    return AVERROR(EINVAL);
}