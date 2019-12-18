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
struct TYPE_5__ {int* vector_dct; int* vector_sig; int /*<<< orphan*/  coeff_reorder; int /*<<< orphan*/  coeff_runv; int /*<<< orphan*/  vector_pdv; int /*<<< orphan*/  vector_fdv; int /*<<< orphan*/  mb_types_stats; } ;
typedef  TYPE_1__ VP56Model ;
struct TYPE_6__ {TYPE_1__* modelp; } ;
typedef  TYPE_2__ VP56Context ;

/* Variables and functions */
 int /*<<< orphan*/  ff_vp56_def_mb_types_stats ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vp6_coeff_order_table_init (TYPE_2__*) ; 
 int /*<<< orphan*/  vp6_def_coeff_reorder ; 
 int /*<<< orphan*/  vp6_def_fdv_vector_model ; 
 int /*<<< orphan*/  vp6_def_pdv_vector_model ; 
 int /*<<< orphan*/  vp6_def_runv_coeff_model ; 

__attribute__((used)) static void vp6_default_models_init(VP56Context *s)
{
    VP56Model *model = s->modelp;

    model->vector_dct[0] = 0xA2;
    model->vector_dct[1] = 0xA4;
    model->vector_sig[0] = 0x80;
    model->vector_sig[1] = 0x80;

    memcpy(model->mb_types_stats, ff_vp56_def_mb_types_stats, sizeof(model->mb_types_stats));
    memcpy(model->vector_fdv, vp6_def_fdv_vector_model, sizeof(model->vector_fdv));
    memcpy(model->vector_pdv, vp6_def_pdv_vector_model, sizeof(model->vector_pdv));
    memcpy(model->coeff_runv, vp6_def_runv_coeff_model, sizeof(model->coeff_runv));
    memcpy(model->coeff_reorder, vp6_def_coeff_reorder, sizeof(model->coeff_reorder));

    vp6_coeff_order_table_init(s);
}