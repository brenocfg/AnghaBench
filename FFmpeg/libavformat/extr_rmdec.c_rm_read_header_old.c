#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  pb; TYPE_1__* priv_data; } ;
struct TYPE_10__ {int /*<<< orphan*/  priv_data; } ;
struct TYPE_9__ {int old_format; } ;
typedef  TYPE_1__ RMDemuxContext ;
typedef  TYPE_2__ AVStream ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 TYPE_2__* avformat_new_stream (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_rm_alloc_rmstream () ; 
 int rm_read_audio_stream_info (TYPE_3__*,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int rm_read_header_old(AVFormatContext *s)
{
    RMDemuxContext *rm = s->priv_data;
    AVStream *st;

    rm->old_format = 1;
    st = avformat_new_stream(s, NULL);
    if (!st)
        return -1;
    st->priv_data = ff_rm_alloc_rmstream();
    if (!st->priv_data)
        return AVERROR(ENOMEM);
    return rm_read_audio_stream_info(s, s->pb, st, st->priv_data, 1);
}