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
typedef  int uint32_t ;
struct TYPE_4__ {int color; } ;
struct TYPE_5__ {int box_flags; TYPE_1__ hclr; int /*<<< orphan*/  buffer; } ;
typedef  TYPE_2__ MovTextContext ;

/* Variables and functions */
 int AV_RB32 (int*) ; 
 int HCLR_BOX ; 
 int /*<<< orphan*/  av_bprint_append_any (int /*<<< orphan*/ *,int*,int) ; 

__attribute__((used)) static void encode_hclr(MovTextContext *s, uint32_t tsmb_type)
{
    uint32_t tsmb_size;
    if (s->box_flags & HCLR_BOX) {
        tsmb_size = 12;
        tsmb_size = AV_RB32(&tsmb_size);
        av_bprint_append_any(&s->buffer, &tsmb_size, 4);
        av_bprint_append_any(&s->buffer, &tsmb_type, 4);
        av_bprint_append_any(&s->buffer, &s->hclr.color, 4);
    }
}