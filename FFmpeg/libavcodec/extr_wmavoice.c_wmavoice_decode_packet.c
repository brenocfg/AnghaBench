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
struct TYPE_8__ {int spillover_nbits; int nb_superframes; int sframe_cache_size; int skip_bits_next; int /*<<< orphan*/  pb; int /*<<< orphan*/  sframe_cache; int /*<<< orphan*/  gb; } ;
typedef  TYPE_1__ WMAVoiceContext ;
struct TYPE_10__ {int block_align; TYPE_1__* priv_data; } ;
struct TYPE_9__ {int size; int /*<<< orphan*/  data; } ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  SFRAME_CACHE_MAXSIZE ; 
 int /*<<< orphan*/  copy_bits (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  flush_put_bits (int /*<<< orphan*/ *) ; 
 int get_bits_count (int /*<<< orphan*/ *) ; 
 int get_bits_left (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_get_bits8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  init_put_bits (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int parse_packet_header (TYPE_1__*) ; 
 int /*<<< orphan*/  skip_bits (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  skip_bits_long (int /*<<< orphan*/ *,int) ; 
 int synth_superframe (TYPE_3__*,void*,int*) ; 

__attribute__((used)) static int wmavoice_decode_packet(AVCodecContext *ctx, void *data,
                                  int *got_frame_ptr, AVPacket *avpkt)
{
    WMAVoiceContext *s = ctx->priv_data;
    GetBitContext *gb = &s->gb;
    int size, res, pos;

    /* Packets are sometimes a multiple of ctx->block_align, with a packet
     * header at each ctx->block_align bytes. However, FFmpeg's ASF demuxer
     * feeds us ASF packets, which may concatenate multiple "codec" packets
     * in a single "muxer" packet, so we artificially emulate that by
     * capping the packet size at ctx->block_align. */
    for (size = avpkt->size; size > ctx->block_align; size -= ctx->block_align);
    init_get_bits8(&s->gb, avpkt->data, size);

    /* size == ctx->block_align is used to indicate whether we are dealing with
     * a new packet or a packet of which we already read the packet header
     * previously. */
    if (!(size % ctx->block_align)) { // new packet header
        if (!size) {
            s->spillover_nbits = 0;
            s->nb_superframes = 0;
        } else {
            if ((res = parse_packet_header(s)) < 0)
                return res;
            s->nb_superframes = res;
        }

        /* If the packet header specifies a s->spillover_nbits, then we want
         * to push out all data of the previous packet (+ spillover) before
         * continuing to parse new superframes in the current packet. */
        if (s->sframe_cache_size > 0) {
            int cnt = get_bits_count(gb);
            if (cnt + s->spillover_nbits > avpkt->size * 8) {
                s->spillover_nbits = avpkt->size * 8 - cnt;
            }
            copy_bits(&s->pb, avpkt->data, size, gb, s->spillover_nbits);
            flush_put_bits(&s->pb);
            s->sframe_cache_size += s->spillover_nbits;
            if ((res = synth_superframe(ctx, data, got_frame_ptr)) == 0 &&
                *got_frame_ptr) {
                cnt += s->spillover_nbits;
                s->skip_bits_next = cnt & 7;
                res = cnt >> 3;
                return res;
            } else
                skip_bits_long (gb, s->spillover_nbits - cnt +
                                get_bits_count(gb)); // resync
        } else if (s->spillover_nbits) {
            skip_bits_long(gb, s->spillover_nbits);  // resync
        }
    } else if (s->skip_bits_next)
        skip_bits(gb, s->skip_bits_next);

    /* Try parsing superframes in current packet */
    s->sframe_cache_size = 0;
    s->skip_bits_next = 0;
    pos = get_bits_left(gb);
    if (s->nb_superframes-- == 0) {
        *got_frame_ptr = 0;
        return size;
    } else if (s->nb_superframes > 0) {
        if ((res = synth_superframe(ctx, data, got_frame_ptr)) < 0) {
            return res;
        } else if (*got_frame_ptr) {
            int cnt = get_bits_count(gb);
            s->skip_bits_next = cnt & 7;
            res = cnt >> 3;
            return res;
        }
    } else if ((s->sframe_cache_size = pos) > 0) {
        /* ... cache it for spillover in next packet */
        init_put_bits(&s->pb, s->sframe_cache, SFRAME_CACHE_MAXSIZE);
        copy_bits(&s->pb, avpkt->data, size, gb, s->sframe_cache_size);
        // FIXME bad - just copy bytes as whole and add use the
        // skip_bits_next field
    }

    return size;
}