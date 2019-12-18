#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint16_t ;
struct TYPE_17__ {int num_substreams; } ;
struct TYPE_13__ {TYPE_8__ hdr; } ;
typedef  TYPE_1__ TrueHDCoreContext ;
struct TYPE_16__ {TYPE_1__* priv_data; } ;
struct TYPE_15__ {int size; int* data; } ;
struct TYPE_14__ {int* bits; int offset; int optional; } ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_2__ AccessUnit ;
typedef  TYPE_3__ AVPacket ;
typedef  TYPE_4__ AVBSFContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int AV_RB16 (int*) ; 
 int /*<<< orphan*/  AV_WB16 (int*,int) ; 
 int /*<<< orphan*/  AV_WL16 (int*,int /*<<< orphan*/ ) ; 
 int FFMIN (int,int) ; 
 int MAX_SUBSTREAMS ; 
 int /*<<< orphan*/  av_assert1 (int) ; 
 int av_packet_make_writable (TYPE_3__*) ; 
 int /*<<< orphan*/  av_packet_unref (TYPE_3__*) ; 
 int ff_bsf_get_packet_ref (TYPE_4__*,TYPE_3__*) ; 
 int /*<<< orphan*/  ff_mlp_checksum16 (int*,int) ; 
 int ff_mlp_read_major_sync (TYPE_4__*,TYPE_8__*,int /*<<< orphan*/ *) ; 
 void* get_bits (int /*<<< orphan*/ *,int) ; 
 int get_bits1 (int /*<<< orphan*/ *) ; 
 int get_bits_count (int /*<<< orphan*/ *) ; 
 int init_get_bits8 (int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int show_bits_long (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int truehd_core_filter(AVBSFContext *ctx, AVPacket *pkt)
{
    TrueHDCoreContext *s = ctx->priv_data;
    GetBitContext gbc;
    AccessUnit units[MAX_SUBSTREAMS];
    int ret, i, last_offset = 0;
    int in_size, out_size;
    int have_header = 0;
    int substream_bytes = 0;
    int end;

    ret = ff_bsf_get_packet_ref(ctx, pkt);
    if (ret < 0)
        return ret;

    if (pkt->size < 4) {
        ret = AVERROR_INVALIDDATA;
        goto fail;
    }

    in_size = (AV_RB16(pkt->data) & 0xFFF) * 2;
    if (in_size < 4 || in_size > pkt->size) {
        ret = AVERROR_INVALIDDATA;
        goto fail;
    }

    ret = init_get_bits8(&gbc, pkt->data + 4, pkt->size - 4);
    if (ret < 0)
        goto fail;

    if (show_bits_long(&gbc, 32) == 0xf8726fba) {
        if ((ret = ff_mlp_read_major_sync(ctx, &s->hdr, &gbc)) < 0)
            goto fail;
        have_header = 1;
    }

    if (s->hdr.num_substreams > MAX_SUBSTREAMS) {
        ret = AVERROR_INVALIDDATA;
        goto fail;
    }

    for (i = 0; i < s->hdr.num_substreams; i++) {
        for (int j = 0; j < 4; j++)
            units[i].bits[j] = get_bits1(&gbc);

        units[i].offset = get_bits(&gbc, 12);
        if (i < 3) {
            last_offset = units[i].offset * 2;
            substream_bytes += 2;
        }

        if (units[i].bits[0]) {
            units[i].optional = get_bits(&gbc, 16);
            if (i < 3)
                substream_bytes += 2;
        }
    }
    end = get_bits_count(&gbc) >> 3;

    out_size = end + 4 + last_offset;
    if (out_size < in_size) {
        int bpos = 0, reduce = end - have_header * 28 - substream_bytes;
        uint16_t parity_nibble, dts = AV_RB16(pkt->data + 2);
        uint16_t auheader;
        uint8_t header[28];

        av_assert1(reduce >= 0 && reduce % 2 == 0);

        if (have_header) {
            memcpy(header, pkt->data + 4, 28);
            header[16]  = (header[16] & 0x0c) | (FFMIN(s->hdr.num_substreams, 3) << 4);
            header[17] &= 0x7f;
            header[25] &= 0xfe;
            AV_WL16(header + 26, ff_mlp_checksum16(header, 26));
        }

        pkt->data += reduce;
        out_size  -= reduce;
        pkt->size  = out_size;

        ret = av_packet_make_writable(pkt);
        if (ret < 0)
            goto fail;

        AV_WB16(pkt->data + 2, dts);
        parity_nibble = dts;
        parity_nibble ^= out_size / 2;

        for (i = 0; i < FFMIN(s->hdr.num_substreams, 3); i++) {
            uint16_t substr_hdr = 0;

            substr_hdr |= (units[i].bits[0] << 15);
            substr_hdr |= (units[i].bits[1] << 14);
            substr_hdr |= (units[i].bits[2] << 13);
            substr_hdr |= (units[i].bits[3] << 12);
            substr_hdr |=  units[i].offset;

            AV_WB16(pkt->data + have_header * 28 + 4 + bpos, substr_hdr);

            parity_nibble ^= substr_hdr;
            bpos          += 2;

            if (units[i].bits[0]) {
                AV_WB16(pkt->data + have_header * 28 + 4 + bpos, units[i].optional);

                parity_nibble ^= units[i].optional;
                bpos          += 2;
            }
        }

        parity_nibble ^= parity_nibble >> 8;
        parity_nibble ^= parity_nibble >> 4;
        parity_nibble &= 0xF;

        auheader  = (parity_nibble ^ 0xF) << 12;
        auheader |= (out_size / 2) & 0x0fff;
        AV_WB16(pkt->data, auheader);

        if (have_header)
            memcpy(pkt->data + 4, header, 28);
    }

fail:
    if (ret < 0)
        av_packet_unref(pkt);

    return ret;
}