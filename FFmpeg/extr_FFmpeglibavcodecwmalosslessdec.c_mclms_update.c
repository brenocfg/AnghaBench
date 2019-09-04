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
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_3__ {int mclms_order; int num_channels; int bits_per_sample; int** channel_residues; int mclms_recent; scalar_t__* mclms_updates; scalar_t__* mclms_prevvalues; int /*<<< orphan*/ * mclms_coeffs_cur; int /*<<< orphan*/ * mclms_coeffs; } ;
typedef  TYPE_1__ WmallDecodeCtx ;

/* Variables and functions */
 scalar_t__ WMASIGN (int) ; 
 scalar_t__ av_clip (int,int,int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__*,int) ; 

__attribute__((used)) static void mclms_update(WmallDecodeCtx *s, int icoef, int *pred)
{
    int i, j, ich, pred_error;
    int order        = s->mclms_order;
    int num_channels = s->num_channels;
    int range        = 1 << (s->bits_per_sample - 1);

    for (ich = 0; ich < num_channels; ich++) {
        pred_error = s->channel_residues[ich][icoef] - pred[ich];
        if (pred_error > 0) {
            for (i = 0; i < order * num_channels; i++)
                s->mclms_coeffs[i + ich * order * num_channels] +=
                    s->mclms_updates[s->mclms_recent + i];
            for (j = 0; j < ich; j++)
                s->mclms_coeffs_cur[ich * num_channels + j] += WMASIGN(s->channel_residues[j][icoef]);
        } else if (pred_error < 0) {
            for (i = 0; i < order * num_channels; i++)
                s->mclms_coeffs[i + ich * order * num_channels] -=
                    s->mclms_updates[s->mclms_recent + i];
            for (j = 0; j < ich; j++)
                s->mclms_coeffs_cur[ich * num_channels + j] -= WMASIGN(s->channel_residues[j][icoef]);
        }
    }

    for (ich = num_channels - 1; ich >= 0; ich--) {
        s->mclms_recent--;
        s->mclms_prevvalues[s->mclms_recent] = av_clip(s->channel_residues[ich][icoef],
            -range, range - 1);
        s->mclms_updates[s->mclms_recent] = WMASIGN(s->channel_residues[ich][icoef]);
    }

    if (s->mclms_recent == 0) {
        memcpy(&s->mclms_prevvalues[order * num_channels],
               s->mclms_prevvalues,
               sizeof(int32_t) * order * num_channels);
        memcpy(&s->mclms_updates[order * num_channels],
               s->mclms_updates,
               sizeof(int32_t) * order * num_channels);
        s->mclms_recent = num_channels * order;
    }
}