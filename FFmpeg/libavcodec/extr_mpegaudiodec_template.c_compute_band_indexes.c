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
struct TYPE_6__ {int block_type; int long_end; int short_start; scalar_t__ switch_point; } ;
struct TYPE_5__ {int sample_rate_index; int /*<<< orphan*/  avctx; } ;
typedef  TYPE_1__ MPADecodeContext ;
typedef  TYPE_2__ GranuleDef ;

/* Variables and functions */
 int /*<<< orphan*/  avpriv_request_sample (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void compute_band_indexes(MPADecodeContext *s, GranuleDef *g)
{
    if (g->block_type == 2) {
        if (g->switch_point) {
            if(s->sample_rate_index == 8)
                avpriv_request_sample(s->avctx, "switch point in 8khz");
            /* if switched mode, we handle the 36 first samples as
                long blocks.  For 8000Hz, we handle the 72 first
                exponents as long blocks */
            if (s->sample_rate_index <= 2)
                g->long_end = 8;
            else
                g->long_end = 6;

            g->short_start = 3;
        } else {
            g->long_end    = 0;
            g->short_start = 0;
        }
    } else {
        g->short_start = 13;
        g->long_end    = 22;
    }
}