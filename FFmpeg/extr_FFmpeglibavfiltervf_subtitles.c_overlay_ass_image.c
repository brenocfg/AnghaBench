#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_9__ {int /*<<< orphan*/  dst_y; int /*<<< orphan*/  dst_x; int /*<<< orphan*/  h; int /*<<< orphan*/  w; int /*<<< orphan*/  stride; int /*<<< orphan*/  bitmap; int /*<<< orphan*/  color; struct TYPE_9__* next; } ;
struct TYPE_8__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  linesize; int /*<<< orphan*/  data; } ;
struct TYPE_7__ {int /*<<< orphan*/  draw; } ;
typedef  int /*<<< orphan*/  FFDrawColor ;
typedef  TYPE_1__ AssContext ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ ASS_Image ;

/* Variables and functions */
 int /*<<< orphan*/  AA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_blend_mask (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_draw_color (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void overlay_ass_image(AssContext *ass, AVFrame *picref,
                              const ASS_Image *image)
{
    for (; image; image = image->next) {
        uint8_t rgba_color[] = {AR(image->color), AG(image->color), AB(image->color), AA(image->color)};
        FFDrawColor color;
        ff_draw_color(&ass->draw, &color, rgba_color);
        ff_blend_mask(&ass->draw, &color,
                      picref->data, picref->linesize,
                      picref->width, picref->height,
                      image->bitmap, image->stride, image->w, image->h,
                      3, 0, image->dst_x, image->dst_y);
    }
}