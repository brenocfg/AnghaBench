#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  scalar_t__ uint64_t ;
typedef  int uint32_t ;
typedef  int ptrdiff_t ;
struct TYPE_9__ {int /*<<< orphan*/  table; } ;
typedef  TYPE_2__ VLC ;
struct TYPE_8__ {int /*<<< orphan*/  (* bswap_buf ) (int*,int*,int) ;} ;
struct TYPE_10__ {int slices; TYPE_7__* avctx; scalar_t__ slice_bits; TYPE_1__ bdsp; int /*<<< orphan*/ ** packed_stream_size; int /*<<< orphan*/ ** packed_stream; int /*<<< orphan*/ ** control_stream_size; int /*<<< orphan*/ ** control_stream; scalar_t__ pack; int /*<<< orphan*/  interlaced; } ;
typedef  TYPE_3__ UtvideoContext ;
struct TYPE_11__ {int /*<<< orphan*/  pix_fmt; } ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_INPUT_BUFFER_PADDING_SIZE ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int AV_RL32 (int const*) ; 
 int /*<<< orphan*/  VLC_BITS ; 
 int /*<<< orphan*/  av_log (TYPE_7__*,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ build_huff (int const*,TYPE_2__*,int*) ; 
 int compute_cmask (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_free_vlc (TYPE_2__*) ; 
 int get_bits_le (int /*<<< orphan*/ *,int) ; 
 int get_bits_left (int /*<<< orphan*/ *) ; 
 int get_vlc2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  init_get_bits (int /*<<< orphan*/ *,scalar_t__,int) ; 
 int init_get_bits8_le (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int*,int*,int) ; 

__attribute__((used)) static int decode_plane(UtvideoContext *c, int plane_no,
                        uint8_t *dst, ptrdiff_t stride,
                        int width, int height,
                        const uint8_t *src, int use_pred)
{
    int i, j, slice, pix;
    int sstart, send;
    VLC vlc;
    GetBitContext gb;
    int ret, prev, fsym;
    const int cmask = compute_cmask(plane_no, c->interlaced, c->avctx->pix_fmt);

    if (c->pack) {
        send = 0;
        for (slice = 0; slice < c->slices; slice++) {
            GetBitContext cbit, pbit;
            uint8_t *dest, *p;

            ret = init_get_bits8_le(&cbit, c->control_stream[plane_no][slice], c->control_stream_size[plane_no][slice]);
            if (ret < 0)
                return ret;

            ret = init_get_bits8_le(&pbit, c->packed_stream[plane_no][slice], c->packed_stream_size[plane_no][slice]);
            if (ret < 0)
                return ret;

            sstart = send;
            send   = (height * (slice + 1) / c->slices) & cmask;
            dest   = dst + sstart * stride;

            if (3 * ((dst + send * stride - dest + 7)/8) > get_bits_left(&cbit))
                return AVERROR_INVALIDDATA;

            for (p = dest; p < dst + send * stride; p += 8) {
                int bits = get_bits_le(&cbit, 3);

                if (bits == 0) {
                    *(uint64_t *) p = 0;
                } else {
                    uint32_t sub = 0x80 >> (8 - (bits + 1)), add;
                    int k;

                    if ((bits + 1) * 8 > get_bits_left(&pbit))
                        return AVERROR_INVALIDDATA;

                    for (k = 0; k < 8; k++) {

                        p[k] = get_bits_le(&pbit, bits + 1);
                        add = (~p[k] & sub) << (8 - bits);
                        p[k] -= sub;
                        p[k] += add;
                    }
                }
            }
        }

        return 0;
    }

    if (build_huff(src, &vlc, &fsym)) {
        av_log(c->avctx, AV_LOG_ERROR, "Cannot build Huffman codes\n");
        return AVERROR_INVALIDDATA;
    }
    if (fsym >= 0) { // build_huff reported a symbol to fill slices with
        send = 0;
        for (slice = 0; slice < c->slices; slice++) {
            uint8_t *dest;

            sstart = send;
            send   = (height * (slice + 1) / c->slices) & cmask;
            dest   = dst + sstart * stride;

            prev = 0x80;
            for (j = sstart; j < send; j++) {
                for (i = 0; i < width; i++) {
                    pix = fsym;
                    if (use_pred) {
                        prev += pix;
                        pix   = prev;
                    }
                    dest[i] = pix;
                }
                dest += stride;
            }
        }
        return 0;
    }

    src      += 256;

    send = 0;
    for (slice = 0; slice < c->slices; slice++) {
        uint8_t *dest;
        int slice_data_start, slice_data_end, slice_size;

        sstart = send;
        send   = (height * (slice + 1) / c->slices) & cmask;
        dest   = dst + sstart * stride;

        // slice offset and size validation was done earlier
        slice_data_start = slice ? AV_RL32(src + slice * 4 - 4) : 0;
        slice_data_end   = AV_RL32(src + slice * 4);
        slice_size       = slice_data_end - slice_data_start;

        if (!slice_size) {
            av_log(c->avctx, AV_LOG_ERROR, "Plane has more than one symbol "
                   "yet a slice has a length of zero.\n");
            goto fail;
        }

        memset(c->slice_bits + slice_size, 0, AV_INPUT_BUFFER_PADDING_SIZE);
        c->bdsp.bswap_buf((uint32_t *) c->slice_bits,
                          (uint32_t *)(src + slice_data_start + c->slices * 4),
                          (slice_data_end - slice_data_start + 3) >> 2);
        init_get_bits(&gb, c->slice_bits, slice_size * 8);

        prev = 0x80;
        for (j = sstart; j < send; j++) {
            for (i = 0; i < width; i++) {
                pix = get_vlc2(&gb, vlc.table, VLC_BITS, 3);
                if (pix < 0) {
                    av_log(c->avctx, AV_LOG_ERROR, "Decoding error\n");
                    goto fail;
                }
                if (use_pred) {
                    prev += pix;
                    pix   = prev;
                }
                dest[i] = pix;
            }
            if (get_bits_left(&gb) < 0) {
                av_log(c->avctx, AV_LOG_ERROR,
                        "Slice decoding ran out of bits\n");
                goto fail;
            }
            dest += stride;
        }
        if (get_bits_left(&gb) > 32)
            av_log(c->avctx, AV_LOG_WARNING,
                   "%d bits left after decoding slice\n", get_bits_left(&gb));
    }

    ff_free_vlc(&vlc);

    return 0;
fail:
    ff_free_vlc(&vlc);
    return AVERROR_INVALIDDATA;
}