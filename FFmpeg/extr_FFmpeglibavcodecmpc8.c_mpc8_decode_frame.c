#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_34__   TYPE_9__ ;
typedef  struct TYPE_33__   TYPE_8__ ;
typedef  struct TYPE_32__   TYPE_7__ ;
typedef  struct TYPE_31__   TYPE_6__ ;
typedef  struct TYPE_30__   TYPE_5__ ;
typedef  struct TYPE_29__   TYPE_4__ ;
typedef  struct TYPE_28__   TYPE_3__ ;
typedef  struct TYPE_27__   TYPE_2__ ;
typedef  struct TYPE_26__   TYPE_1__ ;
typedef  struct TYPE_25__   TYPE_19__ ;
typedef  struct TYPE_24__   TYPE_18__ ;
typedef  struct TYPE_23__   TYPE_12__ ;
typedef  struct TYPE_22__   TYPE_11__ ;
typedef  struct TYPE_21__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_34__ {int /*<<< orphan*/  table; } ;
struct TYPE_33__ {int /*<<< orphan*/  bits; int /*<<< orphan*/  table; } ;
struct TYPE_32__ {int /*<<< orphan*/  table; } ;
struct TYPE_31__ {int /*<<< orphan*/  bits; int /*<<< orphan*/  table; } ;
struct TYPE_30__ {int /*<<< orphan*/  channels; TYPE_1__* priv_data; } ;
struct TYPE_29__ {scalar_t__ extended_data; int /*<<< orphan*/  nb_samples; } ;
struct TYPE_28__ {int size; int /*<<< orphan*/ * data; } ;
struct TYPE_27__ {int* res; int msf; int* scfi; int** scf_idx; } ;
struct TYPE_26__ {scalar_t__ cur_frame; int** Q; int last_bits_used; int maxbands; int last_max_band; int** oldDSCF; scalar_t__ frames; int /*<<< orphan*/  rnd; scalar_t__ MSS; TYPE_2__* bands; } ;
struct TYPE_25__ {int /*<<< orphan*/  table; } ;
struct TYPE_24__ {int /*<<< orphan*/  table; } ;
struct TYPE_23__ {int /*<<< orphan*/  table; } ;
struct TYPE_22__ {int /*<<< orphan*/  table; } ;
struct TYPE_21__ {int /*<<< orphan*/  table; } ;
typedef  TYPE_1__ MPCContext ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_2__ Band ;
typedef  TYPE_3__ AVPacket ;
typedef  TYPE_4__ AVFrame ;
typedef  TYPE_5__ AVCodecContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  FFABS (int) ; 
 int /*<<< orphan*/  MPC8_BANDS_BITS ; 
 int /*<<< orphan*/  MPC8_DSCF0_BITS ; 
 int /*<<< orphan*/  MPC8_DSCF1_BITS ; 
 int /*<<< orphan*/  MPC8_Q1_BITS ; 
 int /*<<< orphan*/  MPC8_Q2_BITS ; 
 int /*<<< orphan*/  MPC8_Q3_BITS ; 
 int /*<<< orphan*/  MPC8_Q9UP_BITS ; 
 int /*<<< orphan*/  MPC8_RES_BITS ; 
 int /*<<< orphan*/  MPC_FRAME_SIZE ; 
 int SAMPLES_PER_BAND ; 
 int av_lfg_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_log (TYPE_5__*,int /*<<< orphan*/ ,char*,int) ; 
 TYPE_19__ band_vlc ; 
 TYPE_18__* dscf_vlc ; 
 int ff_get_buffer (TYPE_5__*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_mpc_dequantize_and_synth (TYPE_1__*,int,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int get_bits (int /*<<< orphan*/ *,int) ; 
 int get_bits1 (int /*<<< orphan*/ *) ; 
 int get_bits_count (int /*<<< orphan*/ *) ; 
 int get_bits_left (int /*<<< orphan*/ *) ; 
 int get_vlc2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int init_get_bits8 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  memset (int**,int /*<<< orphan*/ ,int) ; 
 int mpc8_get_mask (int /*<<< orphan*/ *,int,int) ; 
 int mpc8_get_mod_golomb (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * mpc8_huffq2 ; 
 int* mpc8_idx50 ; 
 int* mpc8_idx51 ; 
 int* mpc8_idx52 ; 
 int* mpc8_thres ; 
 TYPE_12__ q1_vlc ; 
 TYPE_11__* q2_vlc ; 
 int /*<<< orphan*/ * q3_offsets ; 
 TYPE_10__* q3_vlc ; 
 TYPE_9__ q9up_vlc ; 
 int /*<<< orphan*/ * quant_offsets ; 
 TYPE_8__** quant_vlc ; 
 TYPE_7__* res_vlc ; 
 TYPE_6__* scfi_vlc ; 
 int /*<<< orphan*/  skip_bits (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int mpc8_decode_frame(AVCodecContext * avctx, void *data,
                             int *got_frame_ptr, AVPacket *avpkt)
{
    AVFrame *frame     = data;
    const uint8_t *buf = avpkt->data;
    int buf_size = avpkt->size;
    MPCContext *c = avctx->priv_data;
    GetBitContext gb2, *gb = &gb2;
    int i, j, k, ch, cnt, res, t;
    Band *bands = c->bands;
    int off;
    int maxband, keyframe;
    int last[2];

    keyframe = c->cur_frame == 0;

    if(keyframe){
        memset(c->Q, 0, sizeof(c->Q));
        c->last_bits_used = 0;
    }
    if ((res = init_get_bits8(gb, buf, buf_size)) < 0)
        return res;

    skip_bits(gb, c->last_bits_used & 7);

    if(keyframe)
        maxband = mpc8_get_mod_golomb(gb, c->maxbands + 1);
    else{
        maxband = c->last_max_band + get_vlc2(gb, band_vlc.table, MPC8_BANDS_BITS, 2);
        if(maxband > 32) maxband -= 33;
    }

    if (get_bits_left(gb) < 0) {
        *got_frame_ptr = 0;
        return buf_size;
    }

    if(maxband > c->maxbands + 1) {
        av_log(avctx, AV_LOG_ERROR, "maxband %d too large\n",maxband);
        return AVERROR_INVALIDDATA;
    }
    c->last_max_band = maxband;

    /* read subband indexes */
    if(maxband){
        last[0] = last[1] = 0;
        for(i = maxband - 1; i >= 0; i--){
            for(ch = 0; ch < 2; ch++){
                last[ch] = get_vlc2(gb, res_vlc[last[ch] > 2].table, MPC8_RES_BITS, 2) + last[ch];
                if(last[ch] > 15) last[ch] -= 17;
                bands[i].res[ch] = last[ch];
            }
        }
        if(c->MSS){
            int mask;

            cnt = 0;
            for(i = 0; i < maxband; i++)
                if(bands[i].res[0] || bands[i].res[1])
                    cnt++;
            t = mpc8_get_mod_golomb(gb, cnt);
            mask = mpc8_get_mask(gb, cnt, t);
            for(i = maxband - 1; i >= 0; i--)
                if(bands[i].res[0] || bands[i].res[1]){
                    bands[i].msf = mask & 1;
                    mask >>= 1;
                }
        }
    }
    for(i = maxband; i < c->maxbands; i++)
        bands[i].res[0] = bands[i].res[1] = 0;

    if(keyframe){
        for(i = 0; i < 32; i++)
            c->oldDSCF[0][i] = c->oldDSCF[1][i] = 1;
    }

    for(i = 0; i < maxband; i++){
        if(bands[i].res[0] || bands[i].res[1]){
            cnt = !!bands[i].res[0] + !!bands[i].res[1] - 1;
            if(cnt >= 0){
                t = get_vlc2(gb, scfi_vlc[cnt].table, scfi_vlc[cnt].bits, 1);
                if(bands[i].res[0]) bands[i].scfi[0] = t >> (2 * cnt);
                if(bands[i].res[1]) bands[i].scfi[1] = t & 3;
            }
        }
    }

    for(i = 0; i < maxband; i++){
        for(ch = 0; ch < 2; ch++){
            if(!bands[i].res[ch]) continue;

            if(c->oldDSCF[ch][i]){
                bands[i].scf_idx[ch][0] = get_bits(gb, 7) - 6;
                c->oldDSCF[ch][i] = 0;
            }else{
                t = get_vlc2(gb, dscf_vlc[1].table, MPC8_DSCF1_BITS, 2);
                if(t == 64)
                    t += get_bits(gb, 6);
                bands[i].scf_idx[ch][0] = ((bands[i].scf_idx[ch][2] + t - 25) & 0x7F) - 6;
            }
            for(j = 0; j < 2; j++){
                if((bands[i].scfi[ch] << j) & 2)
                    bands[i].scf_idx[ch][j + 1] = bands[i].scf_idx[ch][j];
                else{
                    t = get_vlc2(gb, dscf_vlc[0].table, MPC8_DSCF0_BITS, 2);
                    if(t == 31)
                        t = 64 + get_bits(gb, 6);
                    bands[i].scf_idx[ch][j + 1] = ((bands[i].scf_idx[ch][j] + t - 25) & 0x7F) - 6;
                }
            }
        }
    }

    for(i = 0, off = 0; i < maxband; i++, off += SAMPLES_PER_BAND){
        for(ch = 0; ch < 2; ch++){
            res = bands[i].res[ch];
            switch(res){
            case -1:
                for(j = 0; j < SAMPLES_PER_BAND; j++)
                    c->Q[ch][off + j] = (av_lfg_get(&c->rnd) & 0x3FC) - 510;
                break;
            case 0:
                break;
            case 1:
                for(j = 0; j < SAMPLES_PER_BAND; j += SAMPLES_PER_BAND / 2){
                    cnt = get_vlc2(gb, q1_vlc.table, MPC8_Q1_BITS, 2);
                    t = mpc8_get_mask(gb, 18, cnt);
                    for(k = 0; k < SAMPLES_PER_BAND / 2; k++, t <<= 1)
                        c->Q[ch][off + j + k] = (t & 0x20000) ? (get_bits1(gb) << 1) - 1 : 0;
                }
                break;
            case 2:
                cnt = 6;//2*mpc8_thres[res]
                for(j = 0; j < SAMPLES_PER_BAND; j += 3){
                    t = get_vlc2(gb, q2_vlc[cnt > 3].table, MPC8_Q2_BITS, 2);
                    c->Q[ch][off + j + 0] = mpc8_idx50[t];
                    c->Q[ch][off + j + 1] = mpc8_idx51[t];
                    c->Q[ch][off + j + 2] = mpc8_idx52[t];
                    cnt = (cnt >> 1) + mpc8_huffq2[t];
                }
                break;
            case 3:
            case 4:
                for(j = 0; j < SAMPLES_PER_BAND; j += 2){
                    t = get_vlc2(gb, q3_vlc[res - 3].table, MPC8_Q3_BITS, 2) + q3_offsets[res - 3];
                    c->Q[ch][off + j + 1] = t >> 4;
                    c->Q[ch][off + j + 0] = (t & 8) ? (t & 0xF) - 16 : (t & 0xF);
                }
                break;
            case 5:
            case 6:
            case 7:
            case 8:
                cnt = 2 * mpc8_thres[res];
                for(j = 0; j < SAMPLES_PER_BAND; j++){
                    t = get_vlc2(gb, quant_vlc[res - 5][cnt > mpc8_thres[res]].table, quant_vlc[res - 5][cnt > mpc8_thres[res]].bits, 2) + quant_offsets[res - 5];
                    c->Q[ch][off + j] = t;
                    cnt = (cnt >> 1) + FFABS(c->Q[ch][off + j]);
                }
                break;
            default:
                for(j = 0; j < SAMPLES_PER_BAND; j++){
                    c->Q[ch][off + j] = get_vlc2(gb, q9up_vlc.table, MPC8_Q9UP_BITS, 2);
                    if(res != 9){
                        c->Q[ch][off + j] <<= res - 9;
                        c->Q[ch][off + j] |= get_bits(gb, res - 9);
                    }
                    c->Q[ch][off + j] -= (1 << (res - 2)) - 1;
                }
            }
        }
    }

    frame->nb_samples = MPC_FRAME_SIZE;
    if ((res = ff_get_buffer(avctx, frame, 0)) < 0)
        return res;

    ff_mpc_dequantize_and_synth(c, maxband - 1,
                                (int16_t **)frame->extended_data,
                                avctx->channels);

    c->cur_frame++;

    c->last_bits_used = get_bits_count(gb);
    if(c->cur_frame >= c->frames)
        c->cur_frame = 0;
    if (get_bits_left(gb) < 0) {
        av_log(avctx, AV_LOG_ERROR, "Overread %d\n", -get_bits_left(gb));
        c->last_bits_used = buf_size << 3;
    } else if (c->cur_frame == 0 && get_bits_left(gb) < 8) {// we have only padding left
        c->last_bits_used = buf_size << 3;
    }

    *got_frame_ptr = 1;

    return c->cur_frame ? c->last_bits_used >> 3 : buf_size;
}