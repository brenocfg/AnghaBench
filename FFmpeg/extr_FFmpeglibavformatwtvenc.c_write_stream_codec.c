#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/ * pb; } ;
struct TYPE_12__ {TYPE_1__* codecpar; } ;
struct TYPE_11__ {int /*<<< orphan*/  codec_type; } ;
typedef  TYPE_2__ AVStream ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_wl32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ff_stream1_guid ; 
 int /*<<< orphan*/  finish_chunk (TYPE_3__*) ; 
 int /*<<< orphan*/  write_chunk_header2 (TYPE_3__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  write_pad (int /*<<< orphan*/ *,int) ; 
 int write_stream_codec_info (TYPE_3__*,TYPE_2__*) ; 

__attribute__((used)) static int write_stream_codec(AVFormatContext *s, AVStream * st)
{
    AVIOContext *pb = s->pb;
    int ret;
    write_chunk_header2(s, &ff_stream1_guid, 0x80000000 | 0x01);

    avio_wl32(pb,  0x01);
    write_pad(pb, 4);
    write_pad(pb, 4);

    ret = write_stream_codec_info(s, st);
    if (ret < 0) {
        av_log(s, AV_LOG_ERROR, "write stream codec info failed codec_type(0x%x)\n", st->codecpar->codec_type);
        return -1;
    }

    finish_chunk(s);
    return 0;
}