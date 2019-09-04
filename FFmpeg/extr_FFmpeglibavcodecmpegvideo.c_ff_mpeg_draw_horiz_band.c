#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  low_delay; int /*<<< orphan*/  first_field; int /*<<< orphan*/  picture_structure; TYPE_2__* last_picture_ptr; TYPE_1__* current_picture_ptr; int /*<<< orphan*/  avctx; } ;
struct TYPE_6__ {int /*<<< orphan*/ * f; } ;
struct TYPE_5__ {int /*<<< orphan*/  f; } ;
typedef  TYPE_3__ MpegEncContext ;

/* Variables and functions */
 int /*<<< orphan*/  ff_draw_horiz_band (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ff_mpeg_draw_horiz_band(MpegEncContext *s, int y, int h)
{
    ff_draw_horiz_band(s->avctx, s->current_picture_ptr->f,
                       s->last_picture_ptr ? s->last_picture_ptr->f : NULL, y, h, s->picture_structure,
                       s->first_field, s->low_delay);
}