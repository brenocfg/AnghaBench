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
typedef  int uint32_t ;
typedef  int int16_t ;
struct TYPE_3__ {int* acfilter_coeffs; int acfilter_scaling; int acfilter_order; int num_channels; int** acfilter_prevvalues; int** channel_residues; } ;
typedef  TYPE_1__ WmallDecodeCtx ;

/* Variables and functions */

__attribute__((used)) static void revert_acfilter(WmallDecodeCtx *s, int tile_size)
{
    int ich, pred, i, j;
    int16_t *filter_coeffs = s->acfilter_coeffs;
    int scaling            = s->acfilter_scaling;
    int order              = s->acfilter_order;

    for (ich = 0; ich < s->num_channels; ich++) {
        int *prevvalues = s->acfilter_prevvalues[ich];
        for (i = 0; i < order; i++) {
            pred = 0;
            for (j = 0; j < order; j++) {
                if (i <= j)
                    pred += filter_coeffs[j] * prevvalues[j - i];
                else
                    pred += s->channel_residues[ich][i - j - 1] * filter_coeffs[j];
            }
            pred >>= scaling;
            s->channel_residues[ich][i] += pred;
        }
        for (i = order; i < tile_size; i++) {
            pred = 0;
            for (j = 0; j < order; j++)
                pred += (uint32_t)s->channel_residues[ich][i - j - 1] * filter_coeffs[j];
            pred >>= scaling;
            s->channel_residues[ich][i] += pred;
        }
        for (j = 0; j < order; j++)
            prevvalues[j] = s->channel_residues[ich][tile_size - j - 1];
    }
}