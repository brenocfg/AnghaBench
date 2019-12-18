#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  list_chapter; } ;
typedef  TYPE_1__ hb_chapter_queue_t ;
typedef  TYPE_1__ hb_chapter_queue_item_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  hb_list_close (int /*<<< orphan*/ *) ; 
 TYPE_1__* hb_list_item (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_list_rem (int /*<<< orphan*/ ,TYPE_1__*) ; 

void hb_chapter_queue_close(hb_chapter_queue_t **_q)
{
    hb_chapter_queue_t      * q = *_q;
    hb_chapter_queue_item_t * item;

    if (q == NULL)
    {
        return;
    }
    while ((item = hb_list_item(q->list_chapter, 0)) != NULL)
    {
        hb_list_rem(q->list_chapter, item);
        free(item);
    }
    hb_list_close(&q->list_chapter);
    free(q);
    *_q = NULL;
}