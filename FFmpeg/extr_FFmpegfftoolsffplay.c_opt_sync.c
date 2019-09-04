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
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_SYNC_AUDIO_MASTER ; 
 int /*<<< orphan*/  AV_SYNC_EXTERNAL_CLOCK ; 
 int /*<<< orphan*/  AV_SYNC_VIDEO_MASTER ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char const*,char const*) ; 
 int /*<<< orphan*/  av_sync_type ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static int opt_sync(void *optctx, const char *opt, const char *arg)
{
    if (!strcmp(arg, "audio"))
        av_sync_type = AV_SYNC_AUDIO_MASTER;
    else if (!strcmp(arg, "video"))
        av_sync_type = AV_SYNC_VIDEO_MASTER;
    else if (!strcmp(arg, "ext"))
        av_sync_type = AV_SYNC_EXTERNAL_CLOCK;
    else {
        av_log(NULL, AV_LOG_ERROR, "Unknown value for %s: %s\n", opt, arg);
        exit(1);
    }
    return 0;
}