#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  list_chapter; } ;
typedef  TYPE_2__ hb_chapter_queue_t ;
struct TYPE_11__ {scalar_t__ new_chap; int /*<<< orphan*/  start; } ;
typedef  TYPE_3__ hb_chapter_queue_item_t ;
struct TYPE_9__ {scalar_t__ new_chap; int /*<<< orphan*/  start; } ;
struct TYPE_12__ {TYPE_1__ s; } ;
typedef  TYPE_4__ hb_buffer_t ;

/* Variables and functions */
 int /*<<< orphan*/  hb_list_add (int /*<<< orphan*/ ,TYPE_3__*) ; 
 TYPE_3__* malloc (int) ; 

void hb_chapter_enqueue(hb_chapter_queue_t *q, hb_buffer_t *buf)
{
    /*
     * Chapter markers are sometimes so close we can get a new
     * one before the previous goes through the encoding queue.
     *
     * Dropping markers can cause weird side-effects downstream,
     * including but not limited to missing chapters in the
     * output, so we need to save it somehow.
     */
    hb_chapter_queue_item_t *item = malloc(sizeof(hb_chapter_queue_item_t));
    if (item != NULL)
    {
        item->start = buf->s.start;
        item->new_chap = buf->s.new_chap;
        // Make sure work_loop doesn't also copy the chapter mark
        buf->s.new_chap = 0;
        hb_list_add(q->list_chapter, item);
    }
}