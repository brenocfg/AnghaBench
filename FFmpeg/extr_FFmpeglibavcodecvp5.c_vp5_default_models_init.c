#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int* vector_sig; int* vector_dct; int** vector_pdi; int /*<<< orphan*/  vector_pdv; int /*<<< orphan*/  mb_types_stats; } ;
typedef  TYPE_1__ VP56Model ;
struct TYPE_5__ {TYPE_1__* modelp; } ;
typedef  TYPE_2__ VP56Context ;

/* Variables and functions */
 int /*<<< orphan*/  ff_vp56_def_mb_types_stats ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void vp5_default_models_init(VP56Context *s)
{
    VP56Model *model = s->modelp;
    int i;

    for (i=0; i<2; i++) {
        model->vector_sig[i] = 0x80;
        model->vector_dct[i] = 0x80;
        model->vector_pdi[i][0] = 0x55;
        model->vector_pdi[i][1] = 0x80;
    }
    memcpy(model->mb_types_stats, ff_vp56_def_mb_types_stats, sizeof(model->mb_types_stats));
    memset(model->vector_pdv, 0x80, sizeof(model->vector_pdv));
}