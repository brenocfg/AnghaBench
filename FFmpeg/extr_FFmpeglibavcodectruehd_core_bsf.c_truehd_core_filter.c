#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct TYPE_22__ {int num_substreams; } ;
struct TYPE_18__ {TYPE_8__ hdr; } ;
typedef  TYPE_1__ TrueHDCoreContext ;
struct TYPE_21__ {TYPE_1__* priv_data; } ;
struct TYPE_20__ {int size; int* data; } ;
struct TYPE_19__ {int* bits; int offset; int optional; } ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_2__ AccessUnit ;
typedef  TYPE_3__ AVPacket ;
typedef  TYPE_4__ AVBSFContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_WB16 (int*,int) ; 
 int /*<<< orphan*/  AV_WL16 (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_WN64 (int*,int /*<<< orphan*/ ) ; 
 int FFMIN (int,int) ; 
 int MAX_SUBSTREAMS ; 
 int av_new_packet (TYPE_3__*,int) ; 
 int av_packet_copy_props (TYPE_3__*,TYPE_3__*) ; 
 int /*<<< orphan*/  av_packet_free (TYPE_3__**) ; 
 int /*<<< orphan*/  av_packet_move_ref (TYPE_3__*,TYPE_3__*) ; 
 int /*<<< orphan*/  av_packet_unref (TYPE_3__*) ; 
 int ff_bsf_get_packet (TYPE_4__*,TYPE_3__**) ; 
 int /*<<< orphan*/  ff_mlp_checksum16 (int*,int) ; 
 int ff_mlp_read_major_sync (TYPE_4__*,TYPE_8__*,int /*<<< orphan*/ *) ; 
 int get_bits (int /*<<< orphan*/ *,int) ; 
 int get_bits1 (int /*<<< orphan*/ *) ; 
 int get_bits_count (int /*<<< orphan*/ *) ; 
 int init_get_bits (int /*<<< orphan*/ *,int*,int) ; 
 int init_get_bits8 (int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int show_bits_long (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  skip_bits (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int truehd_core_filter(AVBSFContext *ctx, AVPacket *out)
{
    TrueHDCoreContext *s = ctx->priv_data;
    GetBitContext gbc;
    AccessUnit units[MAX_SUBSTREAMS];
    AVPacket *in;
    int ret, i, size, last_offset = 0;
    int in_size, out_size;
    int have_header = 0;
    int substream_bits = 0;
    int start, end;
    uint16_t dts;

    ret = ff_bsf_get_packet(ctx, &in);
    if (ret < 0)
        return ret;

    if (in->size < 4)
        goto fail;

    ret = init_get_bits(&gbc, in->data, 32);
    if (ret < 0)
        goto fail;

    skip_bits(&gbc, 4);
    in_size = get_bits(&gbc, 12) * 2;
    if (in_size < 4 || in_size > in->size)
        goto fail;

    out_size = in_size;
    dts = get_bits(&gbc, 16);

    ret = init_get_bits8(&gbc, in->data + 4, in->size - 4);
    if (ret < 0)
        goto fail;

    if (show_bits_long(&gbc, 32) == 0xf8726fba) {
        if ((ret = ff_mlp_read_major_sync(ctx, &s->hdr, &gbc)) != 0)
            goto fail;
        have_header = 1;
    }

    if (s->hdr.num_substreams > MAX_SUBSTREAMS)
        goto fail;

    start = get_bits_count(&gbc);
    for (i = 0; i < s->hdr.num_substreams; i++) {
        for (int j = 0; j < 4; j++)
            units[i].bits[j] = get_bits1(&gbc);

        units[i].offset = get_bits(&gbc, 12) * 2;
        if (i < FFMIN(s->hdr.num_substreams, 3)) {
            last_offset = units[i].offset;
            substream_bits += 16;
        }

        if (units[i].bits[0]) {
            units[i].optional = get_bits(&gbc, 16);
            if (i < FFMIN(s->hdr.num_substreams, 3))
                substream_bits += 16;
        }
    }
    end = get_bits_count(&gbc);

    size = ((end + 7) >> 3) + 4 + last_offset;
    if (size >= 0 && size <= in->size)
        out_size = size;
    if (out_size < in_size) {
        int bpos = 0, reduce = (end - start - substream_bits) >> 4;
        uint16_t parity_nibble = 0;
        uint16_t auheader;

        ret = av_new_packet(out, out_size);
        if (ret < 0)
            goto fail;

        AV_WB16(out->data + 2, dts);
        parity_nibble = dts;
        out->size -= reduce * 2;
        parity_nibble ^= out->size / 2;

        if (out_size > 8)
            AV_WN64(out->data + out_size - 8, 0);
        if (have_header) {
            memcpy(out->data + 4, in->data + 4, 28);
            out->data[16 + 4] = (out->data[16 + 4] & 0x0f) | (FFMIN(s->hdr.num_substreams, 3) << 4);
            out->data[25 + 4] = out->data[25 + 4] & 0xfe;
            out->data[26 + 4] = 0xff;
            out->data[27 + 4] = 0xff;
            AV_WL16(out->data + 4 + 26, ff_mlp_checksum16(out->data + 4, 26));
        }

        for (i = 0; i < FFMIN(s->hdr.num_substreams, 3); i++) {
            uint16_t substr_hdr = 0;

            substr_hdr |= (units[i].bits[0] << 15);
            substr_hdr |= (units[i].bits[1] << 14);
            substr_hdr |= (units[i].bits[2] << 13);
            substr_hdr |= (units[i].bits[3] << 12);
            substr_hdr |= (units[i].offset / 2) & 0x0FFF;

            AV_WB16(out->data + have_header * 28 + 4 + bpos, substr_hdr);

            parity_nibble ^= out->data[have_header * 28 + 4 + bpos++];
            parity_nibble ^= out->data[have_header * 28 + 4 + bpos++];

            if (units[i].bits[0]) {
                AV_WB16(out->data + have_header * 28 + 4 + bpos, units[i].optional);

                parity_nibble ^= out->data[have_header * 28 + 4 + bpos++];
                parity_nibble ^= out->data[have_header * 28 + 4 + bpos++];
            }
        }

        parity_nibble ^= parity_nibble >> 8;
        parity_nibble ^= parity_nibble >> 4;
        parity_nibble &= 0xF;

        memcpy(out->data + have_header * 28 + 4 + bpos,
               in->data + 4 + (end >> 3),
               out_size - (4 + (end >> 3)));
        auheader  = (parity_nibble ^ 0xF) << 12;
        auheader |= (out->size / 2) & 0x0fff;
        AV_WB16(out->data, auheader);

        ret = av_packet_copy_props(out, in);
    } else {
        av_packet_move_ref(out, in);
    }

fail:
    if (ret < 0)
        av_packet_unref(out);
    av_packet_free(&in);

    return ret;
}