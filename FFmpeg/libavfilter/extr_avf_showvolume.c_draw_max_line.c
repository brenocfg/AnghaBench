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
struct TYPE_5__ {int b; int h; int /*<<< orphan*/  persistant_max_rgba; TYPE_1__* out; scalar_t__ orientation; } ;
struct TYPE_4__ {int* linesize; int /*<<< orphan*/ ** data; } ;
typedef  TYPE_2__ ShowVolumeContext ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void draw_max_line(ShowVolumeContext *s, int max_draw, int channel)
{
    int k;
    if (s->orientation) { /* vertical */
        uint8_t *dst = s->out->data[0] + max_draw * s->out->linesize[0] + channel * (s->b + s->h) * 4;
        for (k = 0; k < s->h; k++) {
            memcpy(dst + k * 4, s->persistant_max_rgba, sizeof(s->persistant_max_rgba));
        }
    } else { /* horizontal */
        for (k = 0; k < s->h; k++) {
            uint8_t *dst = s->out->data[0] + (channel * s->h + channel * s->b + k) * s->out->linesize[0];
            memcpy(dst + max_draw * 4, s->persistant_max_rgba, sizeof(s->persistant_max_rgba));
        }
    }
}