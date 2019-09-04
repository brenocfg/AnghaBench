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
typedef  int int32_t ;
struct TYPE_4__ {int* vector_buf; int* audio_buf; int* err_buf1; int noise_state; int /*<<< orphan*/  filter; } ;
typedef  TYPE_1__ DssSpContext ;

/* Variables and functions */
 int DSS_SP_FORMULA (int,int,int) ; 
 void* av_clip_int16 (int) ; 
 int /*<<< orphan*/  binary_decreasing_array ; 
 int dss_sp_get_normalize_bits (int*,int) ; 
 int /*<<< orphan*/  dss_sp_scale_vector (int*,int,int) ; 
 int /*<<< orphan*/  dss_sp_shift_sq_add (int*,int*,int*) ; 
 int /*<<< orphan*/  dss_sp_shift_sq_sub (int*,int*,int*) ; 
 int /*<<< orphan*/  dss_sp_unc_decreasing_array ; 
 int /*<<< orphan*/  dss_sp_vec_mult (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int dss_sp_vector_sum (TYPE_1__*,int) ; 

__attribute__((used)) static void dss_sp_sf_synthesis(DssSpContext *p, int32_t lpc_filter,
                                int32_t *dst, int size)
{
    int32_t tmp_buf[15];
    int32_t noise[72];
    int bias, vsum_2 = 0, vsum_1 = 0, v36, normalize_bits;
    int i, tmp;

    if (size > 0) {
        vsum_1 = dss_sp_vector_sum(p, size);

        if (vsum_1 > 0xFFFFF)
            vsum_1 = 0xFFFFF;
    }

    normalize_bits = dss_sp_get_normalize_bits(p->vector_buf, size);

    dss_sp_scale_vector(p->vector_buf, normalize_bits - 3, size);
    dss_sp_scale_vector(p->audio_buf, normalize_bits, 15);
    dss_sp_scale_vector(p->err_buf1, normalize_bits, 15);

    v36 = p->err_buf1[1];

    dss_sp_vec_mult(p->filter, tmp_buf, binary_decreasing_array);
    dss_sp_shift_sq_add(tmp_buf, p->audio_buf, p->vector_buf);

    dss_sp_vec_mult(p->filter, tmp_buf, dss_sp_unc_decreasing_array);
    dss_sp_shift_sq_sub(tmp_buf, p->err_buf1, p->vector_buf);

    /* lpc_filter can be negative */
    lpc_filter = lpc_filter >> 1;
    if (lpc_filter >= 0)
        lpc_filter = 0;

    if (size > 1) {
        for (i = size - 1; i > 0; i--) {
            tmp = DSS_SP_FORMULA(p->vector_buf[i], lpc_filter,
                                 p->vector_buf[i - 1]);
            p->vector_buf[i] = av_clip_int16(tmp);
        }
    }

    tmp              = DSS_SP_FORMULA(p->vector_buf[0], lpc_filter, v36);
    p->vector_buf[0] = av_clip_int16(tmp);

    dss_sp_scale_vector(p->vector_buf, -normalize_bits, size);
    dss_sp_scale_vector(p->audio_buf, -normalize_bits, 15);
    dss_sp_scale_vector(p->err_buf1, -normalize_bits, 15);

    if (size > 0)
        vsum_2 = dss_sp_vector_sum(p, size);

    if (vsum_2 >= 0x40)
        tmp = (vsum_1 << 11) / vsum_2;
    else
        tmp = 1;

    bias     = 409 * tmp >> 15 << 15;
    tmp      = (bias + 32358 * p->noise_state) >> 15;
    noise[0] = av_clip_int16(tmp);

    for (i = 1; i < size; i++) {
        tmp      = (bias + 32358 * noise[i - 1]) >> 15;
        noise[i] = av_clip_int16(tmp);
    }

    p->noise_state = noise[size - 1];
    for (i = 0; i < size; i++) {
        tmp    = (p->vector_buf[i] * noise[i]) >> 11;
        dst[i] = av_clip_int16(tmp);
    }
}