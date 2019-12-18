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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint64_t ;
typedef  int uint32_t ;
struct ws_interval {scalar_t__ ts_start; scalar_t__ ts_end; int type; scalar_t__ damp; scalar_t__ amp0; scalar_t__ phi0; scalar_t__ ddphi; scalar_t__ dphi0; void* channels; } ;
struct wavesynth_context {int nb_inter; struct ws_interval* inter; } ;
typedef  scalar_t__ int64_t ;
typedef  void* int32_t ;
struct TYPE_3__ {int extradata_size; scalar_t__ sample_rate; int /*<<< orphan*/ * extradata; struct wavesynth_context* priv_data; } ;
typedef  TYPE_1__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 void* AV_RL32 (int /*<<< orphan*/ *) ; 
 void* AV_RL64 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 scalar_t__ INT64_MAX ; 
#define  WS_NOISE 129 
#define  WS_SINE 128 
 struct ws_interval* av_calloc (int,int) ; 
 scalar_t__ frac64 (void*,scalar_t__) ; 
 scalar_t__ phi_at (struct ws_interval*,scalar_t__) ; 

__attribute__((used)) static int wavesynth_parse_extradata(AVCodecContext *avc)
{
    struct wavesynth_context *ws = avc->priv_data;
    struct ws_interval *in;
    uint8_t *edata, *edata_end;
    int32_t f1, f2, a1, a2;
    uint32_t phi;
    int64_t dphi1, dphi2, dt, cur_ts = -0x8000000000000000;
    int i;

    if (avc->extradata_size < 4)
        return AVERROR(EINVAL);
    edata = avc->extradata;
    edata_end = edata + avc->extradata_size;
    ws->nb_inter = AV_RL32(edata);
    edata += 4;
    if (ws->nb_inter < 0 || (edata_end - edata) / 24 < ws->nb_inter)
        return AVERROR(EINVAL);
    ws->inter = av_calloc(ws->nb_inter, sizeof(*ws->inter));
    if (!ws->inter)
        return AVERROR(ENOMEM);
    for (i = 0; i < ws->nb_inter; i++) {
        in = &ws->inter[i];
        if (edata_end - edata < 24)
            return AVERROR(EINVAL);
        in->ts_start = AV_RL64(edata +  0);
        in->ts_end   = AV_RL64(edata +  8);
        in->type     = AV_RL32(edata + 16);
        in->channels = AV_RL32(edata + 20);
        edata += 24;
        if (in->ts_start < cur_ts ||
            in->ts_end <= in->ts_start ||
            (uint64_t)in->ts_end - in->ts_start > INT64_MAX
        )
            return AVERROR(EINVAL);
        cur_ts = in->ts_start;
        dt = in->ts_end - in->ts_start;
        switch (in->type) {
            case WS_SINE:
                if (edata_end - edata < 20 || avc->sample_rate <= 0)
                    return AVERROR(EINVAL);
                f1  = AV_RL32(edata +  0);
                f2  = AV_RL32(edata +  4);
                a1  = AV_RL32(edata +  8);
                a2  = AV_RL32(edata + 12);
                phi = AV_RL32(edata + 16);
                edata += 20;
                dphi1 = frac64(f1, (int64_t)avc->sample_rate << 16);
                dphi2 = frac64(f2, (int64_t)avc->sample_rate << 16);
                in->dphi0 = dphi1;
                in->ddphi = (dphi2 - dphi1) / dt;
                if (phi & 0x80000000) {
                    phi &= ~0x80000000;
                    if (phi >= i)
                        return AVERROR(EINVAL);
                    in->phi0 = phi_at(&ws->inter[phi], in->ts_start);
                } else {
                    in->phi0 = (uint64_t)phi << 33;
                }
                break;
            case WS_NOISE:
                if (edata_end - edata < 8)
                    return AVERROR(EINVAL);
                a1  = AV_RL32(edata +  0);
                a2  = AV_RL32(edata +  4);
                edata += 8;
                break;
            default:
                return AVERROR(EINVAL);
        }
        in->amp0 = (uint64_t)a1 << 32;
        in->damp = (int64_t)(((uint64_t)a2 << 32) - ((uint64_t)a1 << 32)) / dt;
    }
    if (edata != edata_end)
        return AVERROR(EINVAL);
    return 0;
}