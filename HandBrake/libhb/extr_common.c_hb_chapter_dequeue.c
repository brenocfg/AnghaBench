#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  list_chapter; } ;
typedef  TYPE_2__ hb_chapter_queue_t ;
struct TYPE_12__ {scalar_t__ start; int /*<<< orphan*/  new_chap; } ;
typedef  TYPE_3__ hb_chapter_queue_item_t ;
struct TYPE_10__ {scalar_t__ start; int /*<<< orphan*/  new_chap; } ;
struct TYPE_13__ {TYPE_1__ s; } ;
typedef  TYPE_4__ hb_buffer_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_3__*) ; 
 TYPE_3__* hb_list_item (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_list_rem (int /*<<< orphan*/ ,TYPE_3__*) ; 

void hb_chapter_dequeue(hb_chapter_queue_t *q, hb_buffer_t *buf)
{
    hb_chapter_queue_item_t *item = hb_list_item(q->list_chapter, 0);
    if (item != NULL)
    {
        if (buf->s.start < item->start)
        {
            // Have not reached the next chapter yet.
            return;
        }

        // we're done with this chapter
        hb_list_rem(q->list_chapter, item);
        buf->s.new_chap = item->new_chap;
        free(item);
    }
}