#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__* lock; } ;
struct TYPE_7__ {int length; TYPE_3__** ofields; TYPE_3__* buffer; } ;
typedef  TYPE_1__ PullupFrame ;
typedef  int /*<<< orphan*/  PullupContext ;

/* Variables and functions */
 int /*<<< orphan*/  copy_field (int /*<<< orphan*/ *,TYPE_3__*,TYPE_3__*,int) ; 
 TYPE_3__* pullup_get_buffer (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pullup_lock_buffer (TYPE_3__*,int) ; 

__attribute__((used)) static void pullup_pack_frame(PullupContext *s, PullupFrame *fr)
{
    int i;

    if (fr->buffer)
        return;

    if (fr->length < 2)
        return; /* FIXME: deal with this */

    for (i = 0; i < 2; i++) {
        if (fr->ofields[i]->lock[i^1])
            continue;

        fr->buffer = fr->ofields[i];
        pullup_lock_buffer(fr->buffer, 2);
        copy_field(s, fr->buffer, fr->ofields[i^1], i^1);
        return;
    }

    fr->buffer = pullup_get_buffer(s, 2);

    copy_field(s, fr->buffer, fr->ofields[0], 0);
    copy_field(s, fr->buffer, fr->ofields[1], 1);
}