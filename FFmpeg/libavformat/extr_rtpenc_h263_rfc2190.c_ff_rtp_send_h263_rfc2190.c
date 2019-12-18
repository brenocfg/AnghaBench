#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  int uint32_t ;
struct H263State {void* vmv2; void* hmv2; void* vmv1; void* hmv1; int /*<<< orphan*/  mba; scalar_t__ gobn; scalar_t__ quant; int /*<<< orphan*/  member_0; } ;
struct H263Info {int tr; int src; int i; int u; int s; int a; int pb; int /*<<< orphan*/  member_0; } ;
typedef  void* int8_t ;
struct TYPE_8__ {TYPE_1__* priv_data; } ;
struct TYPE_7__ {int max_payload_size; int /*<<< orphan*/  cur_timestamp; int /*<<< orphan*/  timestamp; } ;
typedef  TYPE_1__ RTPMuxContext ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_RL16 (scalar_t__ const*) ; 
 int AV_RL32 (scalar_t__ const*) ; 
 int FFMIN (int,int) ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__* ff_h263_find_resync_marker_reverse (scalar_t__ const*,scalar_t__ const*) ; 
 int get_bits (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  init_get_bits (int /*<<< orphan*/ *,scalar_t__ const*,int) ; 
 int /*<<< orphan*/  send_mode_a (TYPE_2__*,struct H263Info*,scalar_t__ const*,int,int,int) ; 
 int /*<<< orphan*/  send_mode_b (TYPE_2__*,struct H263Info*,struct H263State*,scalar_t__ const*,int,int,int,int) ; 
 int /*<<< orphan*/  skip_bits (int /*<<< orphan*/ *,int) ; 

void ff_rtp_send_h263_rfc2190(AVFormatContext *s1, const uint8_t *buf, int size,
                              const uint8_t *mb_info, int mb_info_size)
{
    RTPMuxContext *s = s1->priv_data;
    int len, sbits = 0, ebits = 0;
    GetBitContext gb;
    struct H263Info info = { 0 };
    struct H263State state = { 0 };
    int mb_info_pos = 0, mb_info_count = mb_info_size / 12;
    const uint8_t *buf_base = buf;

    s->timestamp = s->cur_timestamp;

    init_get_bits(&gb, buf, size*8);
    if (get_bits(&gb, 22) == 0x20) { /* Picture Start Code */
        info.tr  = get_bits(&gb, 8);
        skip_bits(&gb, 2); /* PTYPE start, H.261 disambiguation */
        skip_bits(&gb, 3); /* Split screen, document camera, freeze picture release */
        info.src = get_bits(&gb, 3);
        info.i   = get_bits(&gb, 1);
        info.u   = get_bits(&gb, 1);
        info.s   = get_bits(&gb, 1);
        info.a   = get_bits(&gb, 1);
        info.pb  = get_bits(&gb, 1);
    }

    while (size > 0) {
        struct H263State packet_start_state = state;
        len = FFMIN(s->max_payload_size - 8, size);

        /* Look for a better place to split the frame into packets. */
        if (len < size) {
            const uint8_t *end = ff_h263_find_resync_marker_reverse(buf,
                                                                    buf + len);
            len = end - buf;
            if (len == s->max_payload_size - 8) {
                /* Skip mb info prior to the start of the current ptr */
                while (mb_info_pos < mb_info_count) {
                    uint32_t pos = AV_RL32(&mb_info[12*mb_info_pos])/8;
                    if (pos >= buf - buf_base)
                        break;
                    mb_info_pos++;
                }
                /* Find the first mb info past the end pointer */
                while (mb_info_pos + 1 < mb_info_count) {
                    uint32_t pos = AV_RL32(&mb_info[12*(mb_info_pos + 1)])/8;
                    if (pos >= end - buf_base)
                        break;
                    mb_info_pos++;
                }
                if (mb_info_pos < mb_info_count) {
                    const uint8_t *ptr = &mb_info[12*mb_info_pos];
                    /* get position in bits in the input packet at which the next info block should be used */
                    uint32_t bit_pos = AV_RL32(ptr);
                    /* get position in bytes */
                    uint32_t pos_next_mb_info = (bit_pos + 7)/8;
                    /* check if data from the next MB info block should be used */
                    if (pos_next_mb_info <= end - buf_base) {
                        state.quant = ptr[4];
                        state.gobn  = ptr[5];
                        state.mba   = AV_RL16(&ptr[6]);
                        state.hmv1  = (int8_t) ptr[8];
                        state.vmv1  = (int8_t) ptr[9];
                        state.hmv2  = (int8_t) ptr[10];
                        state.vmv2  = (int8_t) ptr[11];
                        ebits = 8 * pos_next_mb_info - bit_pos;
                        len   = pos_next_mb_info - (buf - buf_base);
                        mb_info_pos++;
                    }
                } else {
                    av_log(s1, AV_LOG_ERROR, "Unable to split H.263 packet, "
                           "use -mb_info %d or -ps 1.\n",
                           s->max_payload_size - 8);
                }
            }
        }

        if (size > 2 && !buf[0] && !buf[1])
            send_mode_a(s1, &info, buf, len, ebits, len == size);
        else
            send_mode_b(s1, &info, &packet_start_state, buf, len, sbits,
                        ebits, len == size);

        if (ebits) {
            sbits = 8 - ebits;
            len--;
        } else {
            sbits = 0;
        }
        buf  += len;
        size -= len;
        ebits = 0;
    }
}