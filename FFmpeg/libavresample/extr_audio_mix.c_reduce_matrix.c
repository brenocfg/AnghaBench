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
struct TYPE_3__ {int* output_zero; int* input_skip; int* output_skip; int out_channels; int in_channels; scalar_t__ out_matrix_channels; scalar_t__ in_matrix_channels; } ;
typedef  TYPE_1__ AudioMix ;

/* Variables and functions */
 int FFMIN (int,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void reduce_matrix(AudioMix *am, const double *matrix, int stride)
{
    int i, o;

    memset(am->output_zero, 0, sizeof(am->output_zero));
    memset(am->input_skip,  0, sizeof(am->input_skip));
    memset(am->output_skip, 0, sizeof(am->output_skip));

    /* exclude output channels if they can be zeroed instead of mixed */
    for (o = 0; o < am->out_channels; o++) {
        int zero = 1;

        /* check if the output is always silent */
        for (i = 0; i < am->in_channels; i++) {
            if (matrix[o * stride + i] != 0.0) {
                zero = 0;
                break;
            }
        }
        /* check if the corresponding input channel makes a contribution to
           any output channel */
        if (o < am->in_channels) {
            for (i = 0; i < am->out_channels; i++) {
                if (matrix[i * stride + o] != 0.0) {
                    zero = 0;
                    break;
                }
            }
        }
        if (zero) {
            am->output_zero[o] = 1;
            am->out_matrix_channels--;
            if (o < am->in_channels)
                am->in_matrix_channels--;
        }
    }
    if (am->out_matrix_channels == 0 || am->in_matrix_channels == 0) {
        am->out_matrix_channels = 0;
        am->in_matrix_channels = 0;
        return;
    }

    /* skip input channels that contribute fully only to the corresponding
       output channel */
    for (i = 0; i < FFMIN(am->in_channels, am->out_channels); i++) {
        int skip = 1;

        for (o = 0; o < am->out_channels; o++) {
            int i0;
            if ((o != i && matrix[o * stride + i] != 0.0) ||
                (o == i && matrix[o * stride + i] != 1.0)) {
                skip = 0;
                break;
            }
            /* if the input contributes fully to the output, also check that no
               other inputs contribute to this output */
            if (o == i) {
                for (i0 = 0; i0 < am->in_channels; i0++) {
                    if (i0 != i && matrix[o * stride + i0] != 0.0) {
                        skip = 0;
                        break;
                    }
                }
            }
        }
        if (skip) {
            am->input_skip[i] = 1;
            am->in_matrix_channels--;
        }
    }
    /* skip input channels that do not contribute to any output channel */
    for (; i < am->in_channels; i++) {
        int contrib = 0;

        for (o = 0; o < am->out_channels; o++) {
            if (matrix[o * stride + i] != 0.0) {
                contrib = 1;
                break;
            }
        }
        if (!contrib) {
            am->input_skip[i] = 1;
            am->in_matrix_channels--;
        }
    }
    if (am->in_matrix_channels == 0) {
        am->out_matrix_channels = 0;
        return;
    }

    /* skip output channels that only get full contribution from the
       corresponding input channel */
    for (o = 0; o < FFMIN(am->in_channels, am->out_channels); o++) {
        int skip = 1;
        int o0;

        for (i = 0; i < am->in_channels; i++) {
            if ((o != i && matrix[o * stride + i] != 0.0) ||
                (o == i && matrix[o * stride + i] != 1.0)) {
                skip = 0;
                break;
            }
        }
        /* check if the corresponding input channel makes a contribution to
           any other output channel */
        i = o;
        for (o0 = 0; o0 < am->out_channels; o0++) {
            if (o0 != i && matrix[o0 * stride + i] != 0.0) {
                skip = 0;
                break;
            }
        }
        if (skip) {
            am->output_skip[o] = 1;
            am->out_matrix_channels--;
        }
    }
    if (am->out_matrix_channels == 0) {
        am->in_matrix_channels = 0;
        return;
    }
}