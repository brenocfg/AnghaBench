#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ extradata_size; int /*<<< orphan*/  extradata; } ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  int /*<<< orphan*/  AVFormatContext ;
typedef  TYPE_1__ AVCodecParameters ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int avio_read (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int ff_alloc_extradata (TYPE_1__*,int) ; 

int ff_get_extradata(AVFormatContext *s, AVCodecParameters *par, AVIOContext *pb, int size)
{
    int ret = ff_alloc_extradata(par, size);
    if (ret < 0)
        return ret;
    ret = avio_read(pb, par->extradata, size);
    if (ret != size) {
        av_freep(&par->extradata);
        par->extradata_size = 0;
        av_log(s, AV_LOG_ERROR, "Failed to read extradata of size %d\n", size);
        return ret < 0 ? ret : AVERROR_INVALIDDATA;
    }

    return ret;
}