#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct dshow_ctx {int /*<<< orphan*/ ** device_filter; } ;
typedef  enum dshowSourceFilterType { ____Placeholder_dshowSourceFilterType } dshowSourceFilterType ;
typedef  enum dshowDeviceType { ____Placeholder_dshowDeviceType } dshowDeviceType ;
struct TYPE_5__ {struct dshow_ctx* priv_data; } ;
typedef  int /*<<< orphan*/  ICreateDevEnum ;
typedef  int /*<<< orphan*/  IBaseFilter ;
typedef  TYPE_1__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_freep (char**) ; 
 int dshow_cycle_devices (TYPE_1__*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ **,char**) ; 
 int dshow_cycle_pins (TYPE_1__*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
dshow_list_device_options(AVFormatContext *avctx, ICreateDevEnum *devenum,
                          enum dshowDeviceType devtype, enum dshowSourceFilterType sourcetype)
{
    struct dshow_ctx *ctx = avctx->priv_data;
    IBaseFilter *device_filter = NULL;
    char *device_unique_name = NULL;
    int r;

    if ((r = dshow_cycle_devices(avctx, devenum, devtype, sourcetype, &device_filter, &device_unique_name)) < 0)
        return r;
    ctx->device_filter[devtype] = device_filter;
    if ((r = dshow_cycle_pins(avctx, devtype, sourcetype, device_filter, NULL)) < 0)
        return r;
    av_freep(&device_unique_name);
    return 0;
}