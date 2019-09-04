#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_5__ {int /*<<< orphan*/  pb; TYPE_1__* priv_data; } ;
struct TYPE_4__ {int cache_size; int /*<<< orphan*/ * buffer_ptr; int /*<<< orphan*/ * buffer; int /*<<< orphan*/ * soi_ptr; int /*<<< orphan*/  buffer_size; } ;
typedef  TYPE_1__ MXGContext ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ AV_INPUT_BUFFER_PADDING_SIZE ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/ * av_fast_realloc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int avio_read (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int mxg_update_cache(AVFormatContext *s, unsigned int cache_size)
{
    MXGContext *mxg = s->priv_data;
    unsigned int current_pos = mxg->buffer_ptr - mxg->buffer;
    unsigned int soi_pos;
    uint8_t *buffer;
    int ret;

    /* reallocate internal buffer */
    if (current_pos > current_pos + cache_size)
        return AVERROR(ENOMEM);
    soi_pos = mxg->soi_ptr - mxg->buffer;
    buffer = av_fast_realloc(mxg->buffer, &mxg->buffer_size,
                             current_pos + cache_size +
                             AV_INPUT_BUFFER_PADDING_SIZE);
    if (!buffer)
        return AVERROR(ENOMEM);
    mxg->buffer = buffer;
    mxg->buffer_ptr = mxg->buffer + current_pos;
    if (mxg->soi_ptr) mxg->soi_ptr = mxg->buffer + soi_pos;

    /* get data */
    ret = avio_read(s->pb, mxg->buffer_ptr + mxg->cache_size,
                     cache_size - mxg->cache_size);
    if (ret < 0)
        return ret;

    mxg->cache_size += ret;

    return ret;
}