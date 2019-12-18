#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_9__ ;
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {scalar_t__ type; } ;
struct TYPE_14__ {int /*<<< orphan*/  dectab; int /*<<< orphan*/  cnts; int /*<<< orphan*/ * freqs; int /*<<< orphan*/  cntsum; } ;
struct TYPE_13__ {int /*<<< orphan*/  dectab; int /*<<< orphan*/  cnts; int /*<<< orphan*/ * freqs; int /*<<< orphan*/  cntsum; } ;
struct TYPE_12__ {int /*<<< orphan*/  dectab; int /*<<< orphan*/  cnts; int /*<<< orphan*/ * freqs; int /*<<< orphan*/  cntsum; } ;
struct TYPE_18__ {TYPE_7__* op_model3; TYPE_6__* mv_model3; TYPE_5__* sxy_model3; TYPE_4__ count_model3; TYPE_3__ fill_model3; TYPE_2__ range_model3; TYPE_1__* run_model3; TYPE_9__** pixel_model3; } ;
struct TYPE_17__ {int /*<<< orphan*/  dectab; int /*<<< orphan*/  cnts; int /*<<< orphan*/ * freqs; int /*<<< orphan*/  cntsum; } ;
struct TYPE_16__ {int /*<<< orphan*/  dectab; int /*<<< orphan*/  cnts; int /*<<< orphan*/ * freqs; int /*<<< orphan*/  cntsum; } ;
struct TYPE_15__ {int /*<<< orphan*/  dectab; int /*<<< orphan*/  cnts; int /*<<< orphan*/ * freqs; int /*<<< orphan*/  cntsum; } ;
struct TYPE_11__ {int /*<<< orphan*/  dectab; int /*<<< orphan*/  cnts; int /*<<< orphan*/ * freqs; int /*<<< orphan*/  cntsum; } ;
typedef  TYPE_8__ SCPRContext ;
typedef  TYPE_9__ PixelModel3 ;

/* Variables and functions */
 int /*<<< orphan*/  renew_table3 (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void reinit_tables3(SCPRContext * s)
{
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4096; j++) {
            PixelModel3 *m = &s->pixel_model3[i][j];
            m->type = 0;
        }
    }

    for (int i = 0; i < 6; i++) {
        renew_table3(256, &s->run_model3[i].cntsum,
                     s->run_model3[i].freqs[0], s->run_model3[i].freqs[1],
                     s->run_model3[i].cnts, s->run_model3[i].dectab);
    }

    renew_table3(256, &s->range_model3.cntsum,
                 s->range_model3.freqs[0], s->range_model3.freqs[1],
                 s->range_model3.cnts, s->range_model3.dectab);

    renew_table3(5, &s->fill_model3.cntsum,
                 s->fill_model3.freqs[0], s->fill_model3.freqs[1],
                 s->fill_model3.cnts, s->fill_model3.dectab);

    renew_table3(256, &s->count_model3.cntsum,
                 s->count_model3.freqs[0], s->count_model3.freqs[1],
                 s->count_model3.cnts, s->count_model3.dectab);

    for (int i = 0; i < 4; i++) {
        renew_table3(16, &s->sxy_model3[i].cntsum,
                     s->sxy_model3[i].freqs[0], s->sxy_model3[i].freqs[1],
                     s->sxy_model3[i].cnts, s->sxy_model3[i].dectab);
    }

    for (int i = 0; i < 2; i++) {
        renew_table3(512, &s->mv_model3[i].cntsum,
                     s->mv_model3[i].freqs[0], s->mv_model3[i].freqs[1],
                     s->mv_model3[i].cnts, s->mv_model3[i].dectab);
    }

    for (int i = 0; i < 6; i++) {
        renew_table3(6, &s->op_model3[i].cntsum,
                     s->op_model3[i].freqs[0], s->op_model3[i].freqs[1],
                     s->op_model3[i].cnts, s->op_model3[i].dectab);
    }
}