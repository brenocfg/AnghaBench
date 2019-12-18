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
typedef  int uint8_t ;
struct TYPE_5__ {scalar_t__ mode; size_t pd; int /*<<< orphan*/  is_yuv; } ;
typedef  TYPE_1__ VectorscopeContext ;
struct TYPE_6__ {int* linesize; int** data; int height; int width; } ;
typedef  TYPE_2__ AVFrame ;

/* Variables and functions */
 scalar_t__ COLOR ; 

__attribute__((used)) static void envelope_instant(VectorscopeContext *s, AVFrame *out)
{
    const int dlinesize = out->linesize[0];
    uint8_t *dpd = s->mode == COLOR || !s->is_yuv ? out->data[s->pd] : out->data[0];
    int i, j;

    for (i = 0; i < out->height; i++) {
        for (j = 0; j < out->width; j++) {
            const int pos = i * dlinesize + j;
            const int poa = (i - 1) * dlinesize + j;
            const int pob = (i + 1) * dlinesize + j;

            if (dpd[pos] && (((!j || !dpd[pos - 1]) || ((j == (out->width - 1)) || !dpd[pos + 1]))
                         || ((!i || !dpd[poa]) || ((i == (out->height - 1)) || !dpd[pob])))) {
                dpd[pos] = 255;
            }
        }
    }
}