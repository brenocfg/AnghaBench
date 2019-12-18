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
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int /*<<< orphan*/  AVIO_FLAG_WRITE ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_err2str (int) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char const*,int /*<<< orphan*/ ) ; 
 int avio_open2 (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  int_cb ; 
 int /*<<< orphan*/ * progress_avio ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static int opt_progress(void *optctx, const char *opt, const char *arg)
{
    AVIOContext *avio = NULL;
    int ret;

    if (!strcmp(arg, "-"))
        arg = "pipe:";
    ret = avio_open2(&avio, arg, AVIO_FLAG_WRITE, &int_cb, NULL);
    if (ret < 0) {
        av_log(NULL, AV_LOG_ERROR, "Failed to open progress URL \"%s\": %s\n",
               arg, av_err2str(ret));
        return ret;
    }
    progress_avio = avio;
    return 0;
}