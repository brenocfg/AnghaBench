#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int subframe_count; int number_of_fc_indexes; scalar_t__ gc_index_bits; scalar_t__* fc_index_bits; scalar_t__ gp_index_bits; scalar_t__* pitch_delay_bits; scalar_t__* vq_indexes_bits; scalar_t__ ma_predictor_bits; } ;
struct TYPE_5__ {void** gc_index; void*** fc_indexes; void** gp_index; void** pitch_delay; void** vq_indexes; void* ma_pred_switch; } ;
typedef  TYPE_1__ SiprParameters ;
typedef  TYPE_2__ SiprModeParam ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 void* get_bits (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void decode_parameters(SiprParameters* parms, GetBitContext *pgb,
                              const SiprModeParam *p)
{
    int i, j;

    if (p->ma_predictor_bits)
        parms->ma_pred_switch       = get_bits(pgb, p->ma_predictor_bits);

    for (i = 0; i < 5; i++)
        parms->vq_indexes[i]        = get_bits(pgb, p->vq_indexes_bits[i]);

    for (i = 0; i < p->subframe_count; i++) {
        parms->pitch_delay[i]       = get_bits(pgb, p->pitch_delay_bits[i]);
        if (p->gp_index_bits)
            parms->gp_index[i]      = get_bits(pgb, p->gp_index_bits);

        for (j = 0; j < p->number_of_fc_indexes; j++)
            parms->fc_indexes[i][j] = get_bits(pgb, p->fc_index_bits[j]);

        parms->gc_index[i]          = get_bits(pgb, p->gc_index_bits);
    }
}