#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/ * pb; } ;
struct TYPE_13__ {int index; TYPE_1__* codecpar; } ;
struct TYPE_12__ {int /*<<< orphan*/  codec_type; } ;
typedef  TYPE_2__ AVStream ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  INDEX_BASE ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_wl32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avpriv_set_pts_info (TYPE_2__*,int,int,int) ; 
 int /*<<< orphan*/  ff_SBE2_STREAM_DESC_EVENT ; 
 int /*<<< orphan*/  finish_chunk (TYPE_3__*) ; 
 int /*<<< orphan*/  write_chunk_header2 (TYPE_3__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  write_pad (int /*<<< orphan*/ *,int) ; 
 int write_stream_codec_info (TYPE_3__*,TYPE_2__*) ; 

__attribute__((used)) static int write_stream_data(AVFormatContext *s, AVStream *st)
{
    AVIOContext *pb = s->pb;
    int ret;

    write_chunk_header2(s, &ff_SBE2_STREAM_DESC_EVENT, 0x80000000 | (st->index + INDEX_BASE));
    avio_wl32(pb, 0x00000001);
    avio_wl32(pb, st->index + INDEX_BASE); //stream_id
    avio_wl32(pb, 0x00000001);
    write_pad(pb, 8);

    ret = write_stream_codec_info(s, st);
    if (ret < 0) {
        av_log(s, AV_LOG_ERROR, "write stream codec info failed codec_type(0x%x)\n", st->codecpar->codec_type);
        return -1;
    }
    finish_chunk(s);

    avpriv_set_pts_info(st, 64, 1, 10000000);

    return 0;
}