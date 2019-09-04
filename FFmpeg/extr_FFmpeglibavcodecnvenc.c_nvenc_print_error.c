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
typedef  int /*<<< orphan*/  NVENCSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_log (void*,int /*<<< orphan*/ ,char*,char const*,char const*,int /*<<< orphan*/ ) ; 
 int nvenc_map_error (int /*<<< orphan*/ ,char const**) ; 

__attribute__((used)) static int nvenc_print_error(void *log_ctx, NVENCSTATUS err,
                             const char *error_string)
{
    const char *desc;
    int ret;
    ret = nvenc_map_error(err, &desc);
    av_log(log_ctx, AV_LOG_ERROR, "%s: %s (%d)\n", error_string, desc, err);
    return ret;
}