#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_7__ {int channels; unsigned int in_simd_align_mask; unsigned int out_simd_align_mask; int* ch_map; int /*<<< orphan*/  (* conv_f ) (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int const,int const,int /*<<< orphan*/ *) ;int /*<<< orphan*/ * silence; int /*<<< orphan*/  (* simd_f ) (int /*<<< orphan*/ **,int /*<<< orphan*/  const**,int) ;} ;
struct TYPE_6__ {scalar_t__ planar; int ch_count; int bps; int /*<<< orphan*/ ** ch; } ;
typedef  TYPE_1__ AudioData ;
typedef  TYPE_2__ AudioConvert ;

/* Variables and functions */
 int SWR_CH_MAX ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 int /*<<< orphan*/  av_assert1 (int) ; 
 int /*<<< orphan*/  av_assert2 (int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ **,int /*<<< orphan*/  const**,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ **,int /*<<< orphan*/  const**,int) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int const,int const,int /*<<< orphan*/ *) ; 

int swri_audio_convert(AudioConvert *ctx, AudioData *out, AudioData *in, int len)
{
    int ch;
    int off=0;
    const int os= (out->planar ? 1 :out->ch_count) *out->bps;
    unsigned misaligned = 0;

    av_assert0(ctx->channels == out->ch_count);

    if (ctx->in_simd_align_mask) {
        int planes = in->planar ? in->ch_count : 1;
        unsigned m = 0;
        for (ch = 0; ch < planes; ch++)
            m |= (intptr_t)in->ch[ch];
        misaligned |= m & ctx->in_simd_align_mask;
    }
    if (ctx->out_simd_align_mask) {
        int planes = out->planar ? out->ch_count : 1;
        unsigned m = 0;
        for (ch = 0; ch < planes; ch++)
            m |= (intptr_t)out->ch[ch];
        misaligned |= m & ctx->out_simd_align_mask;
    }

    //FIXME optimize common cases

    if(ctx->simd_f && !ctx->ch_map && !misaligned){
        off = len&~15;
        av_assert1(off>=0);
        av_assert1(off<=len);
        av_assert2(ctx->channels == SWR_CH_MAX || !in->ch[ctx->channels]);
        if(off>0){
            if(out->planar == in->planar){
                int planes = out->planar ? out->ch_count : 1;
                for(ch=0; ch<planes; ch++){
                    ctx->simd_f(out->ch+ch, (const uint8_t **)in->ch+ch, off * (out->planar ? 1 :out->ch_count));
                }
            }else{
                ctx->simd_f(out->ch, (const uint8_t **)in->ch, off);
            }
        }
        if(off == len)
            return 0;
    }

    for(ch=0; ch<ctx->channels; ch++){
        const int ich= ctx->ch_map ? ctx->ch_map[ch] : ch;
        const int is= ich < 0 ? 0 : (in->planar ? 1 : in->ch_count) * in->bps;
        const uint8_t *pi= ich < 0 ? ctx->silence : in->ch[ich];
        uint8_t       *po= out->ch[ch];
        uint8_t *end= po + os*len;
        if(!po)
            continue;
        ctx->conv_f(po+off*os, pi+off*is, is, os, end);
    }
    return 0;
}