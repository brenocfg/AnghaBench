#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
struct TYPE_4__ {int width; int height; } ;
typedef  int /*<<< orphan*/  DxaDecContext ;
typedef  TYPE_1__ AVCodecContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int AV_RB16 (int*) ; 
 int AV_RB32 (int*) ; 
 int /*<<< orphan*/  av_log (TYPE_1__*,int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 
 int* shift1 ; 
 int* shift2 ; 

__attribute__((used)) static int decode_13(AVCodecContext *avctx, DxaDecContext *c, uint8_t* dst,
                     int stride, uint8_t *src, int srcsize, uint8_t *ref)
{
    uint8_t *code, *data, *mv, *msk, *tmp, *tmp2;
    uint8_t *src_end = src + srcsize;
    int i, j, k;
    int type, x, y, d, d2;
    uint32_t mask;

    if (12ULL  + ((avctx->width * avctx->height) >> 4) + AV_RB32(src + 0) + AV_RB32(src + 4) > srcsize)
        return AVERROR_INVALIDDATA;

    code = src  + 12;
    data = code + ((avctx->width * avctx->height) >> 4);
    mv   = data + AV_RB32(src + 0);
    msk  = mv   + AV_RB32(src + 4);

    for(j = 0; j < avctx->height; j += 4){
        for(i = 0; i < avctx->width; i += 4){
            if (data > src_end || mv > src_end || msk > src_end)
                return AVERROR_INVALIDDATA;
            tmp  = dst + i;
            tmp2 = ref + i;
            type = *code++;
            switch(type){
            case 4: // motion compensation
                x = (*mv) >> 4;    if(x & 8) x = 8 - x;
                y = (*mv++) & 0xF; if(y & 8) y = 8 - y;
                if (i < -x || avctx->width  - i - 4 < x ||
                    j < -y || avctx->height - j - 4 < y) {
                    av_log(avctx, AV_LOG_ERROR, "MV %d %d out of bounds\n", x,y);
                    return AVERROR_INVALIDDATA;
                }
                tmp2 += x + y*stride;
            case 0: // skip
            case 5: // skip in method 12
                for(y = 0; y < 4; y++){
                    memcpy(tmp, tmp2, 4);
                    tmp  += stride;
                    tmp2 += stride;
                }
                break;
            case 1:  // masked change
            case 10: // masked change with only half of pixels changed
            case 11: // cases 10-15 are for method 12 only
            case 12:
            case 13:
            case 14:
            case 15:
                if(type == 1){
                    mask = AV_RB16(msk);
                    msk += 2;
                }else{
                    type -= 10;
                    mask = ((msk[0] & 0xF0) << shift1[type]) | ((msk[0] & 0xF) << shift2[type]);
                    msk++;
                }
                for(y = 0; y < 4; y++){
                    for(x = 0; x < 4; x++){
                        tmp[x] = (mask & 0x8000) ? *data++ : tmp2[x];
                        mask <<= 1;
                    }
                    tmp  += stride;
                    tmp2 += stride;
                }
                break;
            case 2: // fill block
                for(y = 0; y < 4; y++){
                    memset(tmp, data[0], 4);
                    tmp += stride;
                }
                data++;
                break;
            case 3: // raw block
                for(y = 0; y < 4; y++){
                    memcpy(tmp, data, 4);
                    data += 4;
                    tmp  += stride;
                }
                break;
            case 8: // subblocks - method 13 only
                mask = *msk++;
                for(k = 0; k < 4; k++){
                    d  = ((k & 1) << 1) + ((k & 2) * stride);
                    d2 = ((k & 1) << 1) + ((k & 2) * stride);
                    tmp2 = ref + i + d2;
                    switch(mask & 0xC0){
                    case 0x80: // motion compensation
                        x = (*mv) >> 4;    if(x & 8) x = 8 - x;
                        y = (*mv++) & 0xF; if(y & 8) y = 8 - y;
                        if (i + 2*(k & 1) < -x || avctx->width  - i - 2*(k & 1) - 2 < x ||
                            j +   (k & 2) < -y || avctx->height - j -   (k & 2) - 2 < y) {
                            av_log(avctx, AV_LOG_ERROR, "MV %d %d out of bounds\n", x,y);
                            return AVERROR_INVALIDDATA;
                        }
                        tmp2 += x + y*stride;
                    case 0x00: // skip
                        tmp[d + 0         ] = tmp2[0];
                        tmp[d + 1         ] = tmp2[1];
                        tmp[d + 0 + stride] = tmp2[0 + stride];
                        tmp[d + 1 + stride] = tmp2[1 + stride];
                        break;
                    case 0x40: // fill
                        tmp[d + 0         ] = data[0];
                        tmp[d + 1         ] = data[0];
                        tmp[d + 0 + stride] = data[0];
                        tmp[d + 1 + stride] = data[0];
                        data++;
                        break;
                    case 0xC0: // raw
                        tmp[d + 0         ] = *data++;
                        tmp[d + 1         ] = *data++;
                        tmp[d + 0 + stride] = *data++;
                        tmp[d + 1 + stride] = *data++;
                        break;
                    }
                    mask <<= 2;
                }
                break;
            case 32: // vector quantization - 2 colors
                mask = AV_RB16(msk);
                msk += 2;
                for(y = 0; y < 4; y++){
                    for(x = 0; x < 4; x++){
                        tmp[x] = data[mask & 1];
                        mask >>= 1;
                    }
                    tmp  += stride;
                    tmp2 += stride;
                }
                data += 2;
                break;
            case 33: // vector quantization - 3 or 4 colors
            case 34:
                mask = AV_RB32(msk);
                msk += 4;
                for(y = 0; y < 4; y++){
                    for(x = 0; x < 4; x++){
                        tmp[x] = data[mask & 3];
                        mask >>= 2;
                    }
                    tmp  += stride;
                    tmp2 += stride;
                }
                data += type - 30;
                break;
            default:
                av_log(avctx, AV_LOG_ERROR, "Unknown opcode %d\n", type);
                return AVERROR_INVALIDDATA;
            }
        }
        dst += stride * 4;
        ref += stride * 4;
    }
    return 0;
}