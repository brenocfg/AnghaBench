#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_11__ {scalar_t__ maxsize; } ;
struct TYPE_10__ {int size; int /*<<< orphan*/  pos; int /*<<< orphan*/  flags; scalar_t__ data; } ;
typedef  TYPE_1__ AVPacket ;
typedef  TYPE_2__ AVIOContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_PKT_FLAG_CORRUPT ; 
 scalar_t__ FFMAX (int,int /*<<< orphan*/ ) ; 
 int FFMIN (int,int) ; 
 int SANE_CHUNK_SIZE ; 
 int av_grow_packet (TYPE_1__*,int) ; 
 int /*<<< orphan*/  av_packet_unref (TYPE_1__*) ; 
 int /*<<< orphan*/  av_shrink_packet (TYPE_1__*,scalar_t__) ; 
 int avio_read (TYPE_2__*,scalar_t__,int) ; 
 int ffio_limit (TYPE_2__*,int) ; 

__attribute__((used)) static int append_packet_chunked(AVIOContext *s, AVPacket *pkt, int size)
{
    int64_t orig_pos   = pkt->pos; // av_grow_packet might reset pos
    int orig_size      = pkt->size;
    int ret;

    do {
        int prev_size = pkt->size;
        int read_size;

        /* When the caller requests a lot of data, limit it to the amount
         * left in file or SANE_CHUNK_SIZE when it is not known. */
        read_size = size;
        if (read_size > SANE_CHUNK_SIZE/10) {
            read_size = ffio_limit(s, read_size);
            // If filesize/maxsize is unknown, limit to SANE_CHUNK_SIZE
            if (s->maxsize < 0)
                read_size = FFMIN(read_size, SANE_CHUNK_SIZE);
        }

        ret = av_grow_packet(pkt, read_size);
        if (ret < 0)
            break;

        ret = avio_read(s, pkt->data + prev_size, read_size);
        if (ret != read_size) {
            av_shrink_packet(pkt, prev_size + FFMAX(ret, 0));
            break;
        }

        size -= read_size;
    } while (size > 0);
    if (size > 0)
        pkt->flags |= AV_PKT_FLAG_CORRUPT;

    pkt->pos = orig_pos;
    if (!pkt->size)
        av_packet_unref(pkt);
    return pkt->size > orig_size ? pkt->size - orig_size : ret;
}