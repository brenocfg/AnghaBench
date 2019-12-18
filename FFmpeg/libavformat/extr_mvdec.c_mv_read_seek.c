#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_7__ {int nb_streams; TYPE_1__* pb; int /*<<< orphan*/ ** streams; TYPE_2__* priv_data; } ;
struct TYPE_6__ {int* frame; } ;
struct TYPE_5__ {int seekable; } ;
typedef  TYPE_2__ MvContext ;
typedef  int /*<<< orphan*/  AVStream ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int AVIO_SEEKABLE_NORMAL ; 
 int AVSEEK_FLAG_BYTE ; 
 int AVSEEK_FLAG_FRAME ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  ENOSYS ; 
 int av_index_search_timestamp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mv_read_seek(AVFormatContext *avctx, int stream_index,
                        int64_t timestamp, int flags)
{
    MvContext *mv = avctx->priv_data;
    AVStream *st = avctx->streams[stream_index];
    int frame, i;

    if ((flags & AVSEEK_FLAG_FRAME) || (flags & AVSEEK_FLAG_BYTE))
        return AVERROR(ENOSYS);

    if (!(avctx->pb->seekable & AVIO_SEEKABLE_NORMAL))
        return AVERROR(EIO);

    frame = av_index_search_timestamp(st, timestamp, flags);
    if (frame < 0)
        return AVERROR_INVALIDDATA;

    for (i = 0; i < avctx->nb_streams; i++)
        mv->frame[i] = frame;
    return 0;
}