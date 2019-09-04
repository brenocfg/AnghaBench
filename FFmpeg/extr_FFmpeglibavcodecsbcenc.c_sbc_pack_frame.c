#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint64_t ;
typedef  int uint32_t ;
struct sbc_frame {int frequency; int blocks; int mode; int allocation; int subbands; int bitpool; int channels; int** scale_factor; int*** sb_sample_f; int /*<<< orphan*/  crc_ctx; } ;
struct TYPE_3__ {int* data; int /*<<< orphan*/  size; } ;
typedef  int /*<<< orphan*/  PutBitContext ;
typedef  TYPE_1__ AVPacket ;

/* Variables and functions */
 int JOINT_STEREO ; 
 int MSBC_SYNCWORD ; 
 int SBC_SYNCWORD ; 
 int SCALE_OUT_BITS ; 
 int STEREO ; 
 int /*<<< orphan*/  ff_sbc_calculate_bits (struct sbc_frame*,int**) ; 
 int ff_sbc_crc8 (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  flush_put_bits (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_put_bits (int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_bits (int /*<<< orphan*/ *,int,int) ; 
 int put_bits_count (int /*<<< orphan*/ *) ; 

__attribute__((used)) static size_t sbc_pack_frame(AVPacket *avpkt, struct sbc_frame *frame,
                             int joint, bool msbc)
{
    PutBitContext pb;

    /* Will copy the header parts for CRC-8 calculation here */
    uint8_t crc_header[11] = { 0 };
    int crc_pos;

    uint32_t audio_sample;

    int ch, sb, blk;        /* channel, subband, block and bit counters */
    int bits[2][8];         /* bits distribution */
    uint32_t levels[2][8];  /* levels are derived from that */
    uint32_t sb_sample_delta[2][8];

    if (msbc) {
        avpkt->data[0] = MSBC_SYNCWORD;
        avpkt->data[1] = 0;
        avpkt->data[2] = 0;
    } else {
        avpkt->data[0] = SBC_SYNCWORD;

        avpkt->data[1]  = (frame->frequency           & 0x03) << 6;
        avpkt->data[1] |= (((frame->blocks >> 2) - 1) & 0x03) << 4;
        avpkt->data[1] |= (frame->mode                & 0x03) << 2;
        avpkt->data[1] |= (frame->allocation          & 0x01) << 1;
        avpkt->data[1] |= ((frame->subbands == 8)     & 0x01) << 0;

        avpkt->data[2] = frame->bitpool;

        if (frame->bitpool > frame->subbands << (4 + (frame->mode == STEREO
                                                   || frame->mode == JOINT_STEREO)))
            return -5;
    }

    /* Can't fill in crc yet */
    crc_header[0] = avpkt->data[1];
    crc_header[1] = avpkt->data[2];
    crc_pos = 16;

    init_put_bits(&pb, avpkt->data + 4, avpkt->size);

    if (frame->mode == JOINT_STEREO) {
        put_bits(&pb, frame->subbands, joint);
        crc_header[crc_pos >> 3] = joint;
        crc_pos += frame->subbands;
    }

    for (ch = 0; ch < frame->channels; ch++) {
        for (sb = 0; sb < frame->subbands; sb++) {
            put_bits(&pb, 4, frame->scale_factor[ch][sb] & 0x0F);
            crc_header[crc_pos >> 3] <<= 4;
            crc_header[crc_pos >> 3] |= frame->scale_factor[ch][sb] & 0x0F;
            crc_pos += 4;
        }
    }

    /* align the last crc byte */
    if (crc_pos % 8)
        crc_header[crc_pos >> 3] <<= 8 - (crc_pos % 8);

    avpkt->data[3] = ff_sbc_crc8(frame->crc_ctx, crc_header, crc_pos);

    ff_sbc_calculate_bits(frame, bits);

    for (ch = 0; ch < frame->channels; ch++) {
        for (sb = 0; sb < frame->subbands; sb++) {
            levels[ch][sb] = ((1 << bits[ch][sb]) - 1) <<
                (32 - (frame->scale_factor[ch][sb] +
                    SCALE_OUT_BITS + 2));
            sb_sample_delta[ch][sb] = (uint32_t) 1 <<
                (frame->scale_factor[ch][sb] +
                    SCALE_OUT_BITS + 1);
        }
    }

    for (blk = 0; blk < frame->blocks; blk++) {
        for (ch = 0; ch < frame->channels; ch++) {
            for (sb = 0; sb < frame->subbands; sb++) {

                if (bits[ch][sb] == 0)
                    continue;

                audio_sample = ((uint64_t) levels[ch][sb] *
                    (sb_sample_delta[ch][sb] +
                    frame->sb_sample_f[blk][ch][sb])) >> 32;

                put_bits(&pb, bits[ch][sb], audio_sample);
            }
        }
    }

    flush_put_bits(&pb);

    return (put_bits_count(&pb) + 7) / 8;
}