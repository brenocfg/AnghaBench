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
typedef  int /*<<< orphan*/  err_msg ;
typedef  int /*<<< orphan*/  AVFilterContext ;

/* Variables and functions */
 int AVERROR_EXTERNAL ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,char*) ; 
 int zimg_get_last_error (char*,int) ; 

__attribute__((used)) static int print_zimg_error(AVFilterContext *ctx)
{
    char err_msg[1024];
    int err_code = zimg_get_last_error(err_msg, sizeof(err_msg));

    av_log(ctx, AV_LOG_ERROR, "code %d: %s\n", err_code, err_msg);

    return AVERROR_EXTERNAL;
}