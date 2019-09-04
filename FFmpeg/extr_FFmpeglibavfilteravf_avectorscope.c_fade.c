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
typedef  scalar_t__ uint8_t ;
struct TYPE_5__ {int h; int w; scalar_t__* fade; TYPE_1__* outpicref; } ;
struct TYPE_4__ {int* linesize; scalar_t__** data; } ;
typedef  TYPE_2__ AudioVectorScopeContext ;

/* Variables and functions */
 scalar_t__ FFMAX (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fade(AudioVectorScopeContext *s)
{
    const int linesize = s->outpicref->linesize[0];
    int i, j;

    if (s->fade[0] || s->fade[1] || s->fade[2]) {
        uint8_t *d = s->outpicref->data[0];
        for (i = 0; i < s->h; i++) {
            for (j = 0; j < s->w*4; j+=4) {
                d[j+0] = FFMAX(d[j+0] - s->fade[0], 0);
                d[j+1] = FFMAX(d[j+1] - s->fade[1], 0);
                d[j+2] = FFMAX(d[j+2] - s->fade[2], 0);
                d[j+3] = FFMAX(d[j+3] - s->fade[3], 0);
            }
            d += linesize;
        }
    }
}