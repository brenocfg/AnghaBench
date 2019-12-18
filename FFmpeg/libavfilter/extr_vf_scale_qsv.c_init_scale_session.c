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
typedef  int /*<<< orphan*/  AVFilterContext ;

/* Variables and functions */
 int init_out_pool (int /*<<< orphan*/ *,int,int) ; 
 int init_out_session (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qsvscale_uninit (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int init_scale_session(AVFilterContext *ctx, int in_width, int in_height,
                              int out_width, int out_height)
{
    int ret;

    qsvscale_uninit(ctx);

    ret = init_out_pool(ctx, out_width, out_height);
    if (ret < 0)
        return ret;

    ret = init_out_session(ctx);
    if (ret < 0)
        return ret;

    return 0;
}