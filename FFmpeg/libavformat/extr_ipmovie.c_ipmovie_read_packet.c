#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * pb; int /*<<< orphan*/ * priv_data; } ;
typedef  int /*<<< orphan*/  IPMVEContext ;
typedef  int /*<<< orphan*/  AVPacket ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_1__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EOF ; 
 int AVERROR_INVALIDDATA ; 
 int CHUNK_BAD ; 
 int CHUNK_END ; 
 int CHUNK_EOF ; 
 int CHUNK_INIT_AUDIO ; 
 int CHUNK_INIT_VIDEO ; 
 int CHUNK_NOMEM ; 
 int CHUNK_SHUTDOWN ; 
 int CHUNK_VIDEO ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  ENOMEM ; 
 int process_ipmovie_chunk (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ipmovie_read_packet(AVFormatContext *s,
                               AVPacket *pkt)
{
    IPMVEContext *ipmovie = s->priv_data;
    AVIOContext *pb = s->pb;
    int ret;

    for (;;) {
    ret = process_ipmovie_chunk(ipmovie, pb, pkt);
    if (ret == CHUNK_BAD)
        ret = AVERROR_INVALIDDATA;
    else if (ret == CHUNK_EOF)
        ret = AVERROR(EIO);
    else if (ret == CHUNK_NOMEM)
        ret = AVERROR(ENOMEM);
    else if (ret == CHUNK_END || ret == CHUNK_SHUTDOWN)
        ret = AVERROR_EOF;
    else if (ret == CHUNK_VIDEO)
        ret = 0;
    else if (ret == CHUNK_INIT_VIDEO || ret == CHUNK_INIT_AUDIO)
        continue;
    else
        continue;

    return ret;
    }
}