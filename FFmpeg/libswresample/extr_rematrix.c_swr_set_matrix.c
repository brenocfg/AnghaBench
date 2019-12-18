#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct SwrContext {double** matrix; double** matrix_flt; int user_in_ch_count; int user_out_ch_count; int rematrix_custom; int /*<<< orphan*/  user_out_ch_layout; int /*<<< orphan*/  user_in_ch_layout; scalar_t__ in_convert; } ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EINVAL ; 
 int av_get_channel_layout_nb_channels (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (double**,int /*<<< orphan*/ ,int) ; 

int swr_set_matrix(struct SwrContext *s, const double *matrix, int stride)
{
    int nb_in, nb_out, in, out;

    if (!s || s->in_convert) // s needs to be allocated but not initialized
        return AVERROR(EINVAL);
    memset(s->matrix, 0, sizeof(s->matrix));
    memset(s->matrix_flt, 0, sizeof(s->matrix_flt));
    nb_in = (s->user_in_ch_count > 0) ? s->user_in_ch_count :
        av_get_channel_layout_nb_channels(s->user_in_ch_layout);
    nb_out = (s->user_out_ch_count > 0) ? s->user_out_ch_count :
        av_get_channel_layout_nb_channels(s->user_out_ch_layout);
    for (out = 0; out < nb_out; out++) {
        for (in = 0; in < nb_in; in++)
            s->matrix_flt[out][in] = s->matrix[out][in] = matrix[in];
        matrix += stride;
    }
    s->rematrix_custom = 1;
    return 0;
}