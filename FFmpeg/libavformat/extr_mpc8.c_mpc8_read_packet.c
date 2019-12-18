#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64_t ;
struct TYPE_10__ {int /*<<< orphan*/  pb; TYPE_1__* priv_data; } ;
struct TYPE_9__ {int duration; scalar_t__ stream_index; } ;
struct TYPE_8__ {scalar_t__ apetag_start; } ;
typedef  TYPE_1__ MPCContext ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EOF ; 
 int /*<<< orphan*/  ENOMEM ; 
 int TAG_AUDIOPACKET ; 
 int TAG_STREAMEND ; 
 scalar_t__ av_get_packet (int /*<<< orphan*/ ,TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  avio_feof (int /*<<< orphan*/ ) ; 
 scalar_t__ avio_tell (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpc8_get_chunk_header (int /*<<< orphan*/ ,int*,scalar_t__*) ; 
 int /*<<< orphan*/  mpc8_handle_chunk (TYPE_3__*,int,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int mpc8_read_packet(AVFormatContext *s, AVPacket *pkt)
{
    MPCContext *c = s->priv_data;
    int tag;
    int64_t pos, size;

    while(!avio_feof(s->pb)){
        pos = avio_tell(s->pb);

        /* don't return bogus packets with the ape tag data */
        if (c->apetag_start && pos >= c->apetag_start)
            return AVERROR_EOF;

        mpc8_get_chunk_header(s->pb, &tag, &size);
        if (size < 0)
            return -1;
        if(tag == TAG_AUDIOPACKET){
            if(av_get_packet(s->pb, pkt, size) < 0)
                return AVERROR(ENOMEM);
            pkt->stream_index = 0;
            pkt->duration     = 1;
            return 0;
        }
        if(tag == TAG_STREAMEND)
            return AVERROR_EOF;
        mpc8_handle_chunk(s, tag, pos, size);
    }
    return AVERROR_EOF;
}