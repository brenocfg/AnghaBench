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
 int /*<<< orphan*/  OPT_INT ; 
 scalar_t__ VSYNC_AUTO ; 
 scalar_t__ VSYNC_CFR ; 
 scalar_t__ VSYNC_DROP ; 
 scalar_t__ VSYNC_PASSTHROUGH ; 
 scalar_t__ VSYNC_VFR ; 
 int /*<<< orphan*/  av_strcasecmp (char const*,char*) ; 
 scalar_t__ parse_number_or_die (char*,char const*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ video_sync_method ; 

__attribute__((used)) static int opt_vsync(void *optctx, const char *opt, const char *arg)
{
    if      (!av_strcasecmp(arg, "cfr"))         video_sync_method = VSYNC_CFR;
    else if (!av_strcasecmp(arg, "vfr"))         video_sync_method = VSYNC_VFR;
    else if (!av_strcasecmp(arg, "passthrough")) video_sync_method = VSYNC_PASSTHROUGH;
    else if (!av_strcasecmp(arg, "drop"))        video_sync_method = VSYNC_DROP;

    if (video_sync_method == VSYNC_AUTO)
        video_sync_method = parse_number_or_die("vsync", arg, OPT_INT, VSYNC_AUTO, VSYNC_VFR);
    return 0;
}