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
typedef  int uint32_t ;
struct TYPE_5__ {int** run_model; int** op_model; int* range_model; int* count_model; int* fill_model; int** sxy_model; int** mv_model; TYPE_1__** pixel_model; } ;
struct TYPE_4__ {int total_freq; int* freq; int* lookup; } ;
typedef  TYPE_2__ SCPRContext ;

/* Variables and functions */

__attribute__((used)) static void reinit_tables(SCPRContext *s)
{
    int comp, i, j;

    for (comp = 0; comp < 3; comp++) {
        for (j = 0; j < 4096; j++) {
            if (s->pixel_model[comp][j].total_freq != 256) {
                for (i = 0; i < 256; i++)
                    s->pixel_model[comp][j].freq[i] = 1;
                for (i = 0; i < 16; i++)
                    s->pixel_model[comp][j].lookup[i] = 16;
                s->pixel_model[comp][j].total_freq = 256;
            }
        }
    }

    for (j = 0; j < 6; j++) {
        uint32_t *p = s->run_model[j];
        for (i = 0; i < 256; i++)
            p[i] = 1;
        p[256] = 256;
    }

    for (j = 0; j < 6; j++) {
        uint32_t *op = s->op_model[j];
        for (i = 0; i < 6; i++)
            op[i] = 1;
        op[6] = 6;
    }

    for (i = 0; i < 256; i++) {
        s->range_model[i] = 1;
        s->count_model[i] = 1;
    }
    s->range_model[256] = 256;
    s->count_model[256] = 256;

    for (i = 0; i < 5; i++) {
        s->fill_model[i] = 1;
    }
    s->fill_model[5] = 5;

    for (j = 0; j < 4; j++) {
        for (i = 0; i < 16; i++) {
            s->sxy_model[j][i] = 1;
        }
        s->sxy_model[j][16] = 16;
    }

    for (i = 0; i < 512; i++) {
        s->mv_model[0][i] = 1;
        s->mv_model[1][i] = 1;
    }
    s->mv_model[0][512] = 512;
    s->mv_model[1][512] = 512;
}