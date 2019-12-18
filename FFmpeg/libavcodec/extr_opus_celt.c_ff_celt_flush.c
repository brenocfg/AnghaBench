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
struct TYPE_5__ {float emph_coeff; int /*<<< orphan*/  pf_gains_new; int /*<<< orphan*/  pf_gains_old; int /*<<< orphan*/  pf_gains; int /*<<< orphan*/  buf; int /*<<< orphan*/  energy; int /*<<< orphan*/ ** prev_energy; } ;
struct TYPE_4__ {int flushed; scalar_t__ seed; TYPE_2__* block; } ;
typedef  TYPE_1__ CeltFrame ;
typedef  TYPE_2__ CeltBlock ;

/* Variables and functions */
 float CELT_EMPH_COEFF ; 
 int /*<<< orphan*/  CELT_ENERGY_SILENCE ; 
 int CELT_MAX_BANDS ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void ff_celt_flush(CeltFrame *f)
{
    int i, j;

    if (f->flushed)
        return;

    for (i = 0; i < 2; i++) {
        CeltBlock *block = &f->block[i];

        for (j = 0; j < CELT_MAX_BANDS; j++)
            block->prev_energy[0][j] = block->prev_energy[1][j] = CELT_ENERGY_SILENCE;

        memset(block->energy, 0, sizeof(block->energy));
        memset(block->buf,    0, sizeof(block->buf));

        memset(block->pf_gains,     0, sizeof(block->pf_gains));
        memset(block->pf_gains_old, 0, sizeof(block->pf_gains_old));
        memset(block->pf_gains_new, 0, sizeof(block->pf_gains_new));

        /* libopus uses CELT_EMPH_COEFF on init, but 0 is better since there's
         * a lesser discontinuity when seeking.
         * The deemphasis functions differ from libopus in that they require
         * an initial state divided by the coefficient. */
        block->emph_coeff = 0.0f / CELT_EMPH_COEFF;
    }
    f->seed = 0;

    f->flushed = 1;
}