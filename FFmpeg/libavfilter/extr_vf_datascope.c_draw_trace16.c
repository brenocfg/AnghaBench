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
struct TYPE_5__ {int nb_values; int nb_comps; int components; int width; int height; size_t* rgba_map; int max; int /*<<< orphan*/ * colors; scalar_t__ oy; scalar_t__ ox; int /*<<< orphan*/  draw; TYPE_1__* values; } ;
struct TYPE_4__ {int* p; } ;
typedef  TYPE_2__ OscilloscopeContext ;
typedef  int /*<<< orphan*/  AVFrame ;

/* Variables and functions */
 int /*<<< orphan*/  draw_line (int /*<<< orphan*/ *,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void draw_trace16(OscilloscopeContext *s, AVFrame *frame)
{
    int i, c;

    for (i = 1; i < s->nb_values; i++) {
        for (c = 0; c < s->nb_comps; c++) {
            if ((1 << c) & s->components) {
                int x = i * s->width / s->nb_values;
                int px = (i - 1) * s->width / s->nb_values;
                int py = s->height - s->values[i-1].p[s->rgba_map[c]] * s->height / s->max;
                int y = s->height - s->values[i].p[s->rgba_map[c]] * s->height / s->max;

                draw_line(&s->draw, s->ox + x, s->oy + y, s->ox + px, s->oy + py, frame, s->colors[c]);
            }
        }
    }
}