#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  start_code ;
struct TYPE_5__ {int (* get_param_set_func ) (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/  const**,size_t*,size_t*,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_1__ VTEncContext ;
struct TYPE_6__ {TYPE_1__* priv_data; } ;
typedef  int /*<<< orphan*/  CMVideoFormatDescriptionRef ;
typedef  TYPE_2__ AVCodecContext ;

/* Variables and functions */
 int AVERROR_EXTERNAL ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*,int) ; 
 int stub1 (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/  const**,size_t*,size_t*,int /*<<< orphan*/ *) ; 
 int stub2 (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/  const**,size_t*,size_t*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int get_params_size(
    AVCodecContext              *avctx,
    CMVideoFormatDescriptionRef vid_fmt,
    size_t                      *size)
{
    VTEncContext *vtctx = avctx->priv_data;
    size_t total_size = 0;
    size_t ps_count;
    int is_count_bad = 0;
    size_t i;
    int status;
    status = vtctx->get_param_set_func(vid_fmt,
                                       0,
                                       NULL,
                                       NULL,
                                       &ps_count,
                                       NULL);
    if (status) {
        is_count_bad = 1;
        ps_count     = 0;
        status       = 0;
    }

    for (i = 0; i < ps_count || is_count_bad; i++) {
        const uint8_t *ps;
        size_t ps_size;
        status = vtctx->get_param_set_func(vid_fmt,
                                           i,
                                           &ps,
                                           &ps_size,
                                           NULL,
                                           NULL);
        if (status) {
            /*
             * When ps_count is invalid, status != 0 ends the loop normally
             * unless we didn't get any parameter sets.
             */
            if (i > 0 && is_count_bad) status = 0;

            break;
        }

        total_size += ps_size + sizeof(start_code);
    }

    if (status) {
        av_log(avctx, AV_LOG_ERROR, "Error getting parameter set sizes: %d\n", status);
        return AVERROR_EXTERNAL;
    }

    *size = total_size;
    return 0;
}