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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  double uint64_t ;
struct TYPE_4__ {scalar_t__ (* sse_line ) (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int const) ;} ;
struct TYPE_5__ {int nb_components; int* planewidth; int* planeheight; TYPE_1__ dsp; } ;
typedef  TYPE_2__ PSNRContext ;

/* Variables and functions */
 scalar_t__ stub1 (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int const) ; 

__attribute__((used)) static inline
void compute_images_mse(PSNRContext *s,
                        const uint8_t *main_data[4], const int main_linesizes[4],
                        const uint8_t *ref_data[4], const int ref_linesizes[4],
                        int w, int h, double mse[4])
{
    int i, c;

    for (c = 0; c < s->nb_components; c++) {
        const int outw = s->planewidth[c];
        const int outh = s->planeheight[c];
        const uint8_t *main_line = main_data[c];
        const uint8_t *ref_line = ref_data[c];
        const int ref_linesize = ref_linesizes[c];
        const int main_linesize = main_linesizes[c];
        uint64_t m = 0;
        for (i = 0; i < outh; i++) {
            m += s->dsp.sse_line(main_line, ref_line, outw);
            ref_line += ref_linesize;
            main_line += main_linesize;
        }
        mse[c] = m / (double)(outw * outh);
    }
}