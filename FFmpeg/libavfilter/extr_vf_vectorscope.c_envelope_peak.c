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
typedef  int uint8_t ;
struct TYPE_7__ {scalar_t__ mode; size_t pd; int** peak; int envelope; int /*<<< orphan*/  is_yuv; } ;
typedef  TYPE_1__ VectorscopeContext ;
struct TYPE_8__ {int* linesize; int** data; int height; int width; } ;
typedef  TYPE_2__ AVFrame ;

/* Variables and functions */
 scalar_t__ COLOR ; 
 int /*<<< orphan*/  envelope_instant (TYPE_1__*,TYPE_2__*) ; 

__attribute__((used)) static void envelope_peak(VectorscopeContext *s, AVFrame *out)
{
    const int dlinesize = out->linesize[0];
    uint8_t *dpd = s->mode == COLOR || !s->is_yuv ? out->data[s->pd] : out->data[0];
    int i, j;

    for (i = 0; i < out->height; i++) {
        for (j = 0; j < out->width; j++) {
            const int pos = i * dlinesize + j;

            if (dpd[pos])
                s->peak[i][j] = 1;
        }
    }

    if (s->envelope == 3)
        envelope_instant(s, out);

    for (i = 0; i < out->height; i++) {
        for (j = 0; j < out->width; j++) {
            const int pos = i * dlinesize + j;

            if (s->peak[i][j] && (((!j || !s->peak[i][j-1]) || ((j == (out->width - 1)) || !s->peak[i][j + 1]))
                              || ((!i || !s->peak[i-1][j]) || ((i == (out->height - 1)) || !s->peak[i + 1][j])))) {
                dpd[pos] = 255;
            }
        }
    }
}