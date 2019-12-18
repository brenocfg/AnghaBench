#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  pvq; } ;
struct TYPE_7__ {int /*<<< orphan*/  lambda; } ;
typedef  int /*<<< orphan*/  OpusRangeCoder ;
typedef  TYPE_1__ OpusPsyContext ;
typedef  TYPE_2__ CeltFrame ;

/* Variables and functions */
 int CELT_MAX_BANDS ; 
 int /*<<< orphan*/  ff_celt_bitalloc (TYPE_2__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ff_opus_rc_enc_init (int /*<<< orphan*/ *) ; 
 float pvq_band_cost (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,int,float*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bands_dist(OpusPsyContext *s, CeltFrame *f, float *total_dist)
{
    int i, tdist = 0.0f;
    OpusRangeCoder dump;

    ff_opus_rc_enc_init(&dump);
    ff_celt_bitalloc(f, &dump, 1);

    for (i = 0; i < CELT_MAX_BANDS; i++) {
        float bits = 0.0f;
        float dist = pvq_band_cost(f->pvq, f, &dump, i, &bits, s->lambda);
        tdist += dist;
    }

    *total_dist = tdist;

    return 0;
}