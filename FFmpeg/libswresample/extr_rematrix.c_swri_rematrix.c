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
typedef  int int16_t ;
struct TYPE_7__ {int bps; scalar_t__ ch_count; scalar_t__* ch; } ;
struct TYPE_6__ {int** matrix_ch; double** matrix; float** matrix_flt; int** matrix32; int /*<<< orphan*/  int_sample_fmt; int /*<<< orphan*/  native_matrix; int /*<<< orphan*/  (* mix_2_1_f ) (scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int,int,int) ;int /*<<< orphan*/  native_simd_matrix; int /*<<< orphan*/  (* mix_2_1_simd ) (scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int,int,int) ;int /*<<< orphan*/  (* mix_1_1_f ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ;int /*<<< orphan*/  (* mix_1_1_simd ) (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int,int) ;int /*<<< orphan*/  in_ch_layout; int /*<<< orphan*/  out_ch_layout; int /*<<< orphan*/  (* mix_any_f ) (scalar_t__*,int /*<<< orphan*/  const**,int /*<<< orphan*/ ,int) ;} ;
typedef  TYPE_1__ SwrContext ;
typedef  TYPE_2__ AudioData ;

/* Variables and functions */
 int /*<<< orphan*/  AV_SAMPLE_FMT_DBLP ; 
 int /*<<< orphan*/  AV_SAMPLE_FMT_FLTP ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 int av_get_bytes_per_sample (int /*<<< orphan*/ ) ; 
 scalar_t__ av_get_channel_layout_nb_channels (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (scalar_t__*,int /*<<< orphan*/  const**,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  stub4 (scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  stub5 (scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  stub6 (scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int,int,int) ; 

int swri_rematrix(SwrContext *s, AudioData *out, AudioData *in, int len, int mustcopy){
    int out_i, in_i, i, j;
    int len1 = 0;
    int off = 0;

    if(s->mix_any_f) {
        s->mix_any_f(out->ch, (const uint8_t **)in->ch, s->native_matrix, len);
        return 0;
    }

    if(s->mix_2_1_simd || s->mix_1_1_simd){
        len1= len&~15;
        off = len1 * out->bps;
    }

    av_assert0(!s->out_ch_layout || out->ch_count == av_get_channel_layout_nb_channels(s->out_ch_layout));
    av_assert0(!s-> in_ch_layout || in ->ch_count == av_get_channel_layout_nb_channels(s-> in_ch_layout));

    for(out_i=0; out_i<out->ch_count; out_i++){
        switch(s->matrix_ch[out_i][0]){
        case 0:
            if(mustcopy)
                memset(out->ch[out_i], 0, len * av_get_bytes_per_sample(s->int_sample_fmt));
            break;
        case 1:
            in_i= s->matrix_ch[out_i][1];
            if(s->matrix[out_i][in_i]!=1.0){
                if(s->mix_1_1_simd && len1)
                    s->mix_1_1_simd(out->ch[out_i]    , in->ch[in_i]    , s->native_simd_matrix, in->ch_count*out_i + in_i, len1);
                if(len != len1)
                    s->mix_1_1_f   (out->ch[out_i]+off, in->ch[in_i]+off, s->native_matrix, in->ch_count*out_i + in_i, len-len1);
            }else if(mustcopy){
                memcpy(out->ch[out_i], in->ch[in_i], len*out->bps);
            }else{
                out->ch[out_i]= in->ch[in_i];
            }
            break;
        case 2: {
            int in_i1 = s->matrix_ch[out_i][1];
            int in_i2 = s->matrix_ch[out_i][2];
            if(s->mix_2_1_simd && len1)
                s->mix_2_1_simd(out->ch[out_i]    , in->ch[in_i1]    , in->ch[in_i2]    , s->native_simd_matrix, in->ch_count*out_i + in_i1, in->ch_count*out_i + in_i2, len1);
            else
                s->mix_2_1_f   (out->ch[out_i]    , in->ch[in_i1]    , in->ch[in_i2]    , s->native_matrix, in->ch_count*out_i + in_i1, in->ch_count*out_i + in_i2, len1);
            if(len != len1)
                s->mix_2_1_f   (out->ch[out_i]+off, in->ch[in_i1]+off, in->ch[in_i2]+off, s->native_matrix, in->ch_count*out_i + in_i1, in->ch_count*out_i + in_i2, len-len1);
            break;}
        default:
            if(s->int_sample_fmt == AV_SAMPLE_FMT_FLTP){
                for(i=0; i<len; i++){
                    float v=0;
                    for(j=0; j<s->matrix_ch[out_i][0]; j++){
                        in_i= s->matrix_ch[out_i][1+j];
                        v+= ((float*)in->ch[in_i])[i] * s->matrix_flt[out_i][in_i];
                    }
                    ((float*)out->ch[out_i])[i]= v;
                }
            }else if(s->int_sample_fmt == AV_SAMPLE_FMT_DBLP){
                for(i=0; i<len; i++){
                    double v=0;
                    for(j=0; j<s->matrix_ch[out_i][0]; j++){
                        in_i= s->matrix_ch[out_i][1+j];
                        v+= ((double*)in->ch[in_i])[i] * s->matrix[out_i][in_i];
                    }
                    ((double*)out->ch[out_i])[i]= v;
                }
            }else{
                for(i=0; i<len; i++){
                    int v=0;
                    for(j=0; j<s->matrix_ch[out_i][0]; j++){
                        in_i= s->matrix_ch[out_i][1+j];
                        v+= ((int16_t*)in->ch[in_i])[i] * s->matrix32[out_i][in_i];
                    }
                    ((int16_t*)out->ch[out_i])[i]= (v + 16384)>>15;
                }
            }
        }
    }
    return 0;
}