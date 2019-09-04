#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;
struct TYPE_6__ {TYPE_1__* priv_data; } ;
struct TYPE_5__ {char* buf; scalar_t__ max_payload_size; } ;
typedef  TYPE_1__ RTPMuxContext ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int AV_RB32 (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  AV_WB16 (char*,int) ; 
 int /*<<< orphan*/  AV_WB32 (char*,int) ; 
 scalar_t__ DIRAC_PIC_NR_SIZE ; 
 int /*<<< orphan*/  DIRAC_RTP_PCODE_HQ_PIC_FRAGMENT ; 
 int FFMIN (scalar_t__,int) ; 
 int get_bits_count (int /*<<< orphan*/ *) ; 
 int get_interleaved_ue_golomb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_get_bits (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  send_packet (TYPE_2__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/  const*,int,int,int,int) ; 

__attribute__((used)) static void send_picture(AVFormatContext *ctx, const uint8_t *buf, int size, int interlaced)
{
    RTPMuxContext *rtp_ctx = ctx->priv_data;
    GetBitContext gc;
    int lvl, second_field;
    uint32_t pic_nr, wavelet_depth, prefix_bytes, size_scaler;
    uint16_t frag_len;
    char *info_hdr = &rtp_ctx->buf[4];

    pic_nr = AV_RB32(&buf[0]);
    buf += DIRAC_PIC_NR_SIZE;
    size -= DIRAC_PIC_NR_SIZE;
    second_field = interlaced && (pic_nr & 0x01);

    init_get_bits(&gc, buf, 8  * size);
                    get_interleaved_ue_golomb(&gc); /* wavelet_idx */
    wavelet_depth = get_interleaved_ue_golomb(&gc);
                    get_interleaved_ue_golomb(&gc); /* num_x */
                    get_interleaved_ue_golomb(&gc); /* num_y */
    prefix_bytes  = get_interleaved_ue_golomb(&gc);
    size_scaler   = get_interleaved_ue_golomb(&gc);
    /* pass the quantization matrices */
    get_interleaved_ue_golomb(&gc);
    for(lvl = 0; lvl < wavelet_depth; lvl++)
    {
        get_interleaved_ue_golomb(&gc);
        get_interleaved_ue_golomb(&gc);
        get_interleaved_ue_golomb(&gc);
    }

    frag_len = (get_bits_count(&gc) + 7) / 8; /* length of transform parameters */

    AV_WB32(&info_hdr[ 0], pic_nr);
    AV_WB16(&info_hdr[ 4], prefix_bytes);
    AV_WB16(&info_hdr[ 6], size_scaler);
    AV_WB16(&info_hdr[ 8], frag_len);
    AV_WB16(&info_hdr[10], 0 /* nr. of slices */);
    send_packet(ctx, DIRAC_RTP_PCODE_HQ_PIC_FRAGMENT, 12, buf, frag_len, interlaced, second_field, 0);
    buf += frag_len;
    size -= frag_len;

    while (size > 0) {
        frag_len = FFMIN(rtp_ctx->max_payload_size - 20 /* pl header */, size);
        AV_WB16(&info_hdr[ 8], frag_len);
        AV_WB16(&info_hdr[10], 1 /* nr. of slices */);
        AV_WB16(&info_hdr[12], 0 /* slice x */);
        AV_WB16(&info_hdr[14], 0 /* slice y */);

        size -= frag_len;
        send_packet(ctx, DIRAC_RTP_PCODE_HQ_PIC_FRAGMENT, 16, buf, frag_len, interlaced, second_field, size > 0 ? 0 : 1);
        buf += frag_len;
    }
}