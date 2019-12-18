#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  char uint8_t ;
struct TYPE_3__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  linesize; int /*<<< orphan*/  data; } ;
typedef  int /*<<< orphan*/  FFDrawContext ;
typedef  int /*<<< orphan*/  FFDrawColor ;
typedef  TYPE_1__ AVFrame ;

/* Variables and functions */
 scalar_t__ avpriv_cga_font ; 
 int /*<<< orphan*/  ff_blend_mask (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void draw_text(FFDrawContext *draw, AVFrame *frame, FFDrawColor *color,
                      int x0, int y0, const uint8_t *text, int vertical)
{
    int x = x0;

    for (; *text; text++) {
        if (*text == '\n') {
            x = x0;
            y0 += 8;
            continue;
        }
        ff_blend_mask(draw, color, frame->data, frame->linesize,
                      frame->width, frame->height,
                      avpriv_cga_font + *text * 8, 1, 8, 8, 0, 0, x, y0);
        if (vertical) {
            x = x0;
            y0 += 8;
        } else {
            x += 8;
        }
    }
}