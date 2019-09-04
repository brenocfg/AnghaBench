#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  int int64_t ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_13__ {int crc; } ;
struct TYPE_12__ {int crc; } ;
struct TYPE_16__ {int pos; int samples; int terms; TYPE_4__* avctx; TYPE_3__* decorr; scalar_t__ zeroes; scalar_t__ zero; scalar_t__ one; TYPE_2__ extra_sc; TYPE_1__ sc; } ;
typedef  TYPE_5__ WavpackFrameContext ;
struct TYPE_15__ {int err_recognition; } ;
struct TYPE_14__ {int value; unsigned int* samplesA; int weightA; int delta; } ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int AV_EF_CRCCHECK ; 
 int AV_EF_EXPLODE ; 
 int const AV_SAMPLE_FMT_FLTP ; 
 int const AV_SAMPLE_FMT_S16P ; 
 int const AV_SAMPLE_FMT_S32P ; 
 int av_get_bytes_per_sample (int const) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int wv_check_crc (TYPE_5__*,int,int) ; 
 int wv_get_value (TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  wv_get_value_float (TYPE_5__*,int*,int) ; 
 void* wv_get_value_integer (TYPE_5__*,int*,int) ; 
 int /*<<< orphan*/  wv_reset_saved_context (TYPE_5__*) ; 

__attribute__((used)) static inline int wv_unpack_mono(WavpackFrameContext *s, GetBitContext *gb,
                                 void *dst, const int type)
{
    int i, j, count = 0;
    int last, t;
    int A, S, T;
    int pos                  = s->pos;
    uint32_t crc             = s->sc.crc;
    uint32_t crc_extra_bits  = s->extra_sc.crc;
    int16_t *dst16           = dst;
    int32_t *dst32           = dst;
    float *dstfl             = dst;

    s->one = s->zero = s->zeroes = 0;
    do {
        T = wv_get_value(s, gb, 0, &last);
        S = 0;
        if (last)
            break;
        for (i = 0; i < s->terms; i++) {
            t = s->decorr[i].value;
            if (t > 8) {
                if (t & 1)
                    A =  2U * s->decorr[i].samplesA[0] - s->decorr[i].samplesA[1];
                else
                    A = (int)(3U * s->decorr[i].samplesA[0] - s->decorr[i].samplesA[1]) >> 1;
                s->decorr[i].samplesA[1] = s->decorr[i].samplesA[0];
                j                        = 0;
            } else {
                A = s->decorr[i].samplesA[pos];
                j = (pos + t) & 7;
            }
            if (type != AV_SAMPLE_FMT_S16P)
                S = T + ((s->decorr[i].weightA * (int64_t)A + 512) >> 10);
            else
                S = T + (unsigned)((int)(s->decorr[i].weightA * (unsigned)A + 512) >> 10);
            if (A && T)
                s->decorr[i].weightA -= ((((T ^ A) >> 30) & 2) - 1) * s->decorr[i].delta;
            s->decorr[i].samplesA[j] = T = S;
        }
        pos = (pos + 1) & 7;
        crc = crc * 3 + S;

        if (type == AV_SAMPLE_FMT_FLTP) {
            *dstfl++ = wv_get_value_float(s, &crc_extra_bits, S);
        } else if (type == AV_SAMPLE_FMT_S32P) {
            *dst32++ = wv_get_value_integer(s, &crc_extra_bits, S);
        } else {
            *dst16++ = wv_get_value_integer(s, &crc_extra_bits, S);
        }
        count++;
    } while (!last && count < s->samples);

    wv_reset_saved_context(s);

    if (last && count < s->samples) {
        int size = av_get_bytes_per_sample(type);
        memset((uint8_t*)dst + count*size, 0, (s->samples-count)*size);
    }

    if (s->avctx->err_recognition & AV_EF_CRCCHECK) {
        int ret = wv_check_crc(s, crc, crc_extra_bits);
        if (ret < 0 && s->avctx->err_recognition & AV_EF_EXPLODE)
            return ret;
    }

    return 0;
}