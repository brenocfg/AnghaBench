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
struct TYPE_3__ {int mclms_order; int num_channels; int mclms_recent; int* mclms_coeffs; int* mclms_coeffs_cur; int mclms_scaling; scalar_t__** channel_residues; scalar_t__* mclms_prevvalues; int /*<<< orphan*/ * is_channel_coded; } ;
typedef  TYPE_1__ WmallDecodeCtx ;

/* Variables and functions */

__attribute__((used)) static void mclms_predict(WmallDecodeCtx *s, int icoef, int *pred)
{
    int ich, i;
    int order        = s->mclms_order;
    int num_channels = s->num_channels;

    for (ich = 0; ich < num_channels; ich++) {
        pred[ich] = 0;
        if (!s->is_channel_coded[ich])
            continue;
        for (i = 0; i < order * num_channels; i++)
            pred[ich] += (uint32_t)s->mclms_prevvalues[i + s->mclms_recent] *
                         s->mclms_coeffs[i + order * num_channels * ich];
        for (i = 0; i < ich; i++)
            pred[ich] += (uint32_t)s->channel_residues[i][icoef] *
                         s->mclms_coeffs_cur[i + num_channels * ich];
        pred[ich] += 1 << s->mclms_scaling - 1;
        pred[ich] >>= s->mclms_scaling;
        s->channel_residues[ich][icoef] += pred[ich];
    }
}