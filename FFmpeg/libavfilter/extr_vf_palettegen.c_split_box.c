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
struct range_box {int start; int len; int variance; void* color; int /*<<< orphan*/  sorted_by; } ;
struct TYPE_3__ {int /*<<< orphan*/  refs; int /*<<< orphan*/  nb_boxes; struct range_box* boxes; } ;
typedef  TYPE_1__ PaletteGenContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_assert0 (int) ; 
 void* get_avg_color (int /*<<< orphan*/ ,struct range_box*) ; 

__attribute__((used)) static void split_box(PaletteGenContext *s, struct range_box *box, int n)
{
    struct range_box *new_box = &s->boxes[s->nb_boxes++];
    new_box->start     = n + 1;
    new_box->len       = box->start + box->len - new_box->start;
    new_box->sorted_by = box->sorted_by;
    box->len -= new_box->len;

    av_assert0(box->len     >= 1);
    av_assert0(new_box->len >= 1);

    box->color     = get_avg_color(s->refs, box);
    new_box->color = get_avg_color(s->refs, new_box);
    box->variance     = -1;
    new_box->variance = -1;
}