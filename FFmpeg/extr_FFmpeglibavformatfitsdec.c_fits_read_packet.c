#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ int64_t ;
struct TYPE_18__ {int len; } ;
struct TYPE_17__ {int /*<<< orphan*/  pb; TYPE_1__* priv_data; } ;
struct TYPE_16__ {int size; int /*<<< orphan*/  pts; scalar_t__ data; int /*<<< orphan*/  flags; scalar_t__ stream_index; } ;
struct TYPE_15__ {int /*<<< orphan*/  pts; scalar_t__ first_image; } ;
typedef  int /*<<< orphan*/  FITSHeader ;
typedef  TYPE_1__ FITSContext ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVFormatContext ;
typedef  TYPE_4__ AVBPrint ;

/* Variables and functions */
 scalar_t__ AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_BPRINT_SIZE_UNLIMITED ; 
 int /*<<< orphan*/  AV_PKT_FLAG_KEY ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  FITS_BLOCK_SIZE ; 
 int /*<<< orphan*/  STATE_SIMPLE ; 
 int /*<<< orphan*/  STATE_XTENSION ; 
 scalar_t__ av_bprint_finalize (TYPE_4__*,char**) ; 
 int /*<<< orphan*/  av_bprint_init (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_bprint_is_complete (TYPE_4__*) ; 
 int /*<<< orphan*/  av_freep (char**) ; 
 scalar_t__ av_new_packet (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  av_packet_unref (TYPE_2__*) ; 
 scalar_t__ avio_read (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ avio_skip (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  avpriv_fits_header_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ is_image (TYPE_3__*,TYPE_1__*,int /*<<< orphan*/ *,TYPE_4__*,scalar_t__*) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,char*,int) ; 

__attribute__((used)) static int fits_read_packet(AVFormatContext *s, AVPacket *pkt)
{
    int64_t pos, ret;
    uint64_t size;
    FITSContext *fits = s->priv_data;
    FITSHeader header;
    AVBPrint avbuf;
    char *buf;

    if (fits->first_image) {
        avpriv_fits_header_init(&header, STATE_SIMPLE);
    } else {
        avpriv_fits_header_init(&header, STATE_XTENSION);
    }

    av_bprint_init(&avbuf, FITS_BLOCK_SIZE, AV_BPRINT_SIZE_UNLIMITED);
    while ((ret = is_image(s, fits, &header, &avbuf, &size)) == 0) {
        pos = avio_skip(s->pb, size);
        if (pos < 0)
            return pos;

        av_bprint_finalize(&avbuf, NULL);
        av_bprint_init(&avbuf, FITS_BLOCK_SIZE, AV_BPRINT_SIZE_UNLIMITED);
        avpriv_fits_header_init(&header, STATE_XTENSION);
    }
    if (ret < 0)
        goto fail;

    if (!av_bprint_is_complete(&avbuf)) {
        ret = AVERROR(ENOMEM);
        goto fail;
    }

    // Header is sent with the first line removed...
    ret = av_new_packet(pkt, avbuf.len - 80 + size);
    if (ret < 0)
        goto fail;

    pkt->stream_index = 0;
    pkt->flags |= AV_PKT_FLAG_KEY;

    ret = av_bprint_finalize(&avbuf, &buf);
    if (ret < 0) {
        av_packet_unref(pkt);
        return ret;
    }

    memcpy(pkt->data, buf + 80, avbuf.len - 80);
    pkt->size = avbuf.len - 80;
    av_freep(&buf);
    ret = avio_read(s->pb, pkt->data + pkt->size, size);
    if (ret < 0) {
        av_packet_unref(pkt);
        return ret;
    }

    pkt->size += ret;
    pkt->pts = fits->pts;
    fits->pts++;

    return 0;

fail:
    av_bprint_finalize(&avbuf, NULL);
    return ret;
}