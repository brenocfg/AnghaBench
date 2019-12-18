#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  double int64_t ;
struct TYPE_15__ {int /*<<< orphan*/  pb; TYPE_1__** streams; TYPE_3__* priv_data; } ;
struct TYPE_14__ {int packet_number; int pack_header_freq; double last_scr; int packet_size; long long mux_rate; int system_header_freq; scalar_t__ is_mpeg2; scalar_t__ is_dvd; scalar_t__ is_svcd; scalar_t__ is_vcd; } ;
struct TYPE_13__ {int id; scalar_t__ packet_number; int bytes_to_iframe; int lpcm_align; int max_buffer_size; int* lpcm_header; int /*<<< orphan*/  fifo; scalar_t__ align_iframe; } ;
struct TYPE_12__ {TYPE_2__* priv_data; } ;
typedef  TYPE_2__ StreamInfo ;
typedef  TYPE_3__ MpegMuxContext ;
typedef  TYPE_4__ AVFormatContext ;

/* Variables and functions */
 int AUDIO_ID ; 
 int /*<<< orphan*/  AV_LOG_TRACE ; 
 double AV_NOPTS_VALUE ; 
 int PRIVATE_STREAM_1 ; 
 int PRIVATE_STREAM_2 ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 int /*<<< orphan*/  av_fifo_generic_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,void (*) (void*,void*,int)) ; 
 int av_fifo_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*,int,double) ; 
 int /*<<< orphan*/  avio_flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_w8 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  avio_wb16 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  avio_wb32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  avio_write (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int get_nb_frames (TYPE_4__*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int put_pack_header (TYPE_4__*,int /*<<< orphan*/ *,double) ; 
 int /*<<< orphan*/  put_padding_packet (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int put_system_header (TYPE_4__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  put_timestamp (int /*<<< orphan*/ ,int,double) ; 

__attribute__((used)) static int flush_packet(AVFormatContext *ctx, int stream_index,
                        int64_t pts, int64_t dts, int64_t scr, int trailer_size)
{
    MpegMuxContext *s  = ctx->priv_data;
    StreamInfo *stream = ctx->streams[stream_index]->priv_data;
    uint8_t *buf_ptr;
    int size, payload_size, startcode, id, stuffing_size, i, header_len;
    int packet_size;
    uint8_t buffer[128];
    int zero_trail_bytes = 0;
    int pad_packet_bytes = 0;
    int pes_flags;
    /* "general" pack without data specific to one stream? */
    int general_pack = 0;
    int nb_frames;

    id = stream->id;

    av_log(ctx, AV_LOG_TRACE, "packet ID=%2x PTS=%0.3f\n", id, pts / 90000.0);

    buf_ptr = buffer;

    if ((s->packet_number % s->pack_header_freq) == 0 || s->last_scr != scr) {
        /* output pack and systems header if needed */
        size        = put_pack_header(ctx, buf_ptr, scr);
        buf_ptr    += size;
        s->last_scr = scr;

        if (s->is_vcd) {
            /* there is exactly one system header for each stream in a VCD MPEG,
             * One in the very first video packet and one in the very first
             * audio packet (see VCD standard p. IV-7 and IV-8). */

            if (stream->packet_number == 0) {
                size     = put_system_header(ctx, buf_ptr, id);
                buf_ptr += size;
            }
        } else if (s->is_dvd) {
            if (stream->align_iframe || s->packet_number == 0) {
                int PES_bytes_to_fill = s->packet_size - size - 10;

                if (pts != AV_NOPTS_VALUE) {
                    if (dts != pts)
                        PES_bytes_to_fill -= 5 + 5;
                    else
                        PES_bytes_to_fill -= 5;
                }

                if (stream->bytes_to_iframe == 0 || s->packet_number == 0) {
                    size     = put_system_header(ctx, buf_ptr, 0);
                    buf_ptr += size;
                    size     = buf_ptr - buffer;
                    avio_write(ctx->pb, buffer, size);

                    avio_wb32(ctx->pb, PRIVATE_STREAM_2);
                    avio_wb16(ctx->pb, 0x03d4);     // length
                    avio_w8(ctx->pb, 0x00);         // substream ID, 00=PCI
                    for (i = 0; i < 979; i++)
                        avio_w8(ctx->pb, 0x00);

                    avio_wb32(ctx->pb, PRIVATE_STREAM_2);
                    avio_wb16(ctx->pb, 0x03fa);     // length
                    avio_w8(ctx->pb, 0x01);         // substream ID, 01=DSI
                    for (i = 0; i < 1017; i++)
                        avio_w8(ctx->pb, 0x00);

                    memset(buffer, 0, 128);
                    buf_ptr = buffer;
                    s->packet_number++;
                    stream->align_iframe = 0;
                    // FIXME: rounding and first few bytes of each packet
                    scr        += s->packet_size * 90000LL /
                                  (s->mux_rate * 50LL);
                    size        = put_pack_header(ctx, buf_ptr, scr);
                    s->last_scr = scr;
                    buf_ptr    += size;
                    /* GOP Start */
                } else if (stream->bytes_to_iframe < PES_bytes_to_fill) {
                    pad_packet_bytes = PES_bytes_to_fill -
                                       stream->bytes_to_iframe;
                }
            }
        } else {
            if ((s->packet_number % s->system_header_freq) == 0) {
                size     = put_system_header(ctx, buf_ptr, 0);
                buf_ptr += size;
            }
        }
    }
    size = buf_ptr - buffer;
    avio_write(ctx->pb, buffer, size);

    packet_size = s->packet_size - size;

    if (s->is_vcd && (id & 0xe0) == AUDIO_ID)
        /* The VCD standard demands that 20 zero bytes follow
         * each audio pack (see standard p. IV-8). */
        zero_trail_bytes += 20;

    if ((s->is_vcd && stream->packet_number == 0) ||
        (s->is_svcd && s->packet_number == 0)) {
        /* for VCD the first pack of each stream contains only the pack header,
         * the system header and lots of padding (see VCD standard p. IV-6).
         * In the case of an audio pack, 20 zero bytes are also added at
         * the end. */
        /* For SVCD we fill the very first pack to increase compatibility with
         * some DVD players. Not mandated by the standard. */
        if (s->is_svcd)
            /* the system header refers to both streams and no stream data */
            general_pack = 1;
        pad_packet_bytes = packet_size - zero_trail_bytes;
    }

    packet_size -= pad_packet_bytes + zero_trail_bytes;

    if (packet_size > 0) {
        /* packet header size */
        packet_size -= 6;

        /* packet header */
        if (s->is_mpeg2) {
            header_len = 3;
            if (stream->packet_number == 0)
                header_len += 3; /* PES extension */
            header_len += 1; /* obligatory stuffing byte */
        } else {
            header_len = 0;
        }
        if (pts != AV_NOPTS_VALUE) {
            if (dts != pts)
                header_len += 5 + 5;
            else
                header_len += 5;
        } else {
            if (!s->is_mpeg2)
                header_len++;
        }

        payload_size = packet_size - header_len;
        if (id < 0xc0) {
            startcode     = PRIVATE_STREAM_1;
            payload_size -= 1;
            if (id >= 0x40) {
                payload_size -= 3;
                if (id >= 0xa0)
                    payload_size -= 3;
            }
        } else {
            startcode = 0x100 + id;
        }

        stuffing_size = payload_size - av_fifo_size(stream->fifo);

        // first byte does not fit -> reset pts/dts + stuffing
        if (payload_size <= trailer_size && pts != AV_NOPTS_VALUE) {
            int timestamp_len = 0;
            if (dts != pts)
                timestamp_len += 5;
            if (pts != AV_NOPTS_VALUE)
                timestamp_len += s->is_mpeg2 ? 5 : 4;
            pts         =
            dts         = AV_NOPTS_VALUE;
            header_len -= timestamp_len;
            if (s->is_dvd && stream->align_iframe) {
                pad_packet_bytes += timestamp_len;
                packet_size      -= timestamp_len;
            } else {
                payload_size += timestamp_len;
            }
            stuffing_size += timestamp_len;
            if (payload_size > trailer_size)
                stuffing_size += payload_size - trailer_size;
        }

        // can't use padding, so use stuffing
        if (pad_packet_bytes > 0 && pad_packet_bytes <= 7) {
            packet_size  += pad_packet_bytes;
            payload_size += pad_packet_bytes; // undo the previous adjustment
            if (stuffing_size < 0)
                stuffing_size = pad_packet_bytes;
            else
                stuffing_size += pad_packet_bytes;
            pad_packet_bytes = 0;
        }

        if (stuffing_size < 0)
            stuffing_size = 0;

        if (startcode == PRIVATE_STREAM_1 && id >= 0xa0) {
            if (payload_size < av_fifo_size(stream->fifo))
                stuffing_size += payload_size % stream->lpcm_align;
        }

        if (stuffing_size > 16) {   /* <=16 for MPEG-1, <=32 for MPEG-2 */
            pad_packet_bytes += stuffing_size;
            packet_size      -= stuffing_size;
            payload_size     -= stuffing_size;
            stuffing_size     = 0;
        }

        nb_frames = get_nb_frames(ctx, stream, payload_size - stuffing_size);

        avio_wb32(ctx->pb, startcode);

        avio_wb16(ctx->pb, packet_size);

        if (!s->is_mpeg2)
            for (i = 0; i < stuffing_size; i++)
                avio_w8(ctx->pb, 0xff);

        if (s->is_mpeg2) {
            avio_w8(ctx->pb, 0x80); /* mpeg2 id */

            pes_flags = 0;

            if (pts != AV_NOPTS_VALUE) {
                pes_flags |= 0x80;
                if (dts != pts)
                    pes_flags |= 0x40;
            }

            /* Both the MPEG-2 and the SVCD standards demand that the
             * P-STD_buffer_size field be included in the first packet of
             * every stream. (see SVCD standard p. 26 V.2.3.1 and V.2.3.2
             * and MPEG-2 standard 2.7.7) */
            if (stream->packet_number == 0)
                pes_flags |= 0x01;

            avio_w8(ctx->pb, pes_flags); /* flags */
            avio_w8(ctx->pb, header_len - 3 + stuffing_size);

            if (pes_flags & 0x80)  /* write pts */
                put_timestamp(ctx->pb, (pes_flags & 0x40) ? 0x03 : 0x02, pts);
            if (pes_flags & 0x40)  /* write dts */
                put_timestamp(ctx->pb, 0x01, dts);

            if (pes_flags & 0x01) {  /* write pes extension */
                avio_w8(ctx->pb, 0x10); /* flags */

                /* P-STD buffer info */
                if ((id & 0xe0) == AUDIO_ID)
                    avio_wb16(ctx->pb, 0x4000 | stream->max_buffer_size / 128);
                else
                    avio_wb16(ctx->pb, 0x6000 | stream->max_buffer_size / 1024);
            }
        } else {
            if (pts != AV_NOPTS_VALUE) {
                if (dts != pts) {
                    put_timestamp(ctx->pb, 0x03, pts);
                    put_timestamp(ctx->pb, 0x01, dts);
                } else {
                    put_timestamp(ctx->pb, 0x02, pts);
                }
            } else {
                avio_w8(ctx->pb, 0x0f);
            }
        }

        if (s->is_mpeg2) {
            /* special stuffing byte that is always written
             * to prevent accidental generation of start codes. */
            avio_w8(ctx->pb, 0xff);

            for (i = 0; i < stuffing_size; i++)
                avio_w8(ctx->pb, 0xff);
        }

        if (startcode == PRIVATE_STREAM_1) {
            avio_w8(ctx->pb, id);
            if (id >= 0xa0) {
                /* LPCM (XXX: check nb_frames) */
                avio_w8(ctx->pb, 7);
                avio_wb16(ctx->pb, 4); /* skip 3 header bytes */
                avio_w8(ctx->pb, stream->lpcm_header[0]);
                avio_w8(ctx->pb, stream->lpcm_header[1]);
                avio_w8(ctx->pb, stream->lpcm_header[2]);
            } else if (id >= 0x40) {
                /* AC-3 */
                avio_w8(ctx->pb, nb_frames);
                avio_wb16(ctx->pb, trailer_size + 1);
            }
        }

        /* output data */
        av_assert0(payload_size - stuffing_size <= av_fifo_size(stream->fifo));
        av_fifo_generic_read(stream->fifo, ctx->pb,
                             payload_size - stuffing_size,
                             (void (*)(void*, void*, int))avio_write);
        stream->bytes_to_iframe -= payload_size - stuffing_size;
    } else {
        payload_size  =
        stuffing_size = 0;
    }

    if (pad_packet_bytes > 0)
        put_padding_packet(ctx, ctx->pb, pad_packet_bytes);

    for (i = 0; i < zero_trail_bytes; i++)
        avio_w8(ctx->pb, 0x00);

    avio_flush(ctx->pb);

    s->packet_number++;

    /* only increase the stream packet number if this pack actually contains
     * something that is specific to this stream! I.e. a dedicated header
     * or some data. */
    if (!general_pack)
        stream->packet_number++;

    return payload_size - stuffing_size;
}