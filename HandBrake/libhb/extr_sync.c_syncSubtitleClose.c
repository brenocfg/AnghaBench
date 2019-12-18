#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {TYPE_3__* stream; } ;
typedef  TYPE_4__ sync_delta_t ;
typedef  TYPE_4__ hb_work_private_t ;
struct TYPE_15__ {TYPE_4__* private_data; } ;
typedef  TYPE_6__ hb_work_object_t ;
struct TYPE_11__ {int /*<<< orphan*/  list_current; } ;
struct TYPE_12__ {TYPE_1__ sanitizer; } ;
struct TYPE_13__ {TYPE_2__ subtitle; int /*<<< orphan*/  scr_delay_queue; int /*<<< orphan*/  in_queue; int /*<<< orphan*/  delta_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_4__*) ; 
 int /*<<< orphan*/  hb_buffer_list_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_list_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_list_empty (int /*<<< orphan*/ *) ; 
 TYPE_4__* hb_list_item (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_list_rem (int /*<<< orphan*/ ,TYPE_4__*) ; 

__attribute__((used)) static void syncSubtitleClose( hb_work_object_t * w )
{
    hb_work_private_t * pv   = w->private_data;

    if (pv == NULL)
    {
        return;
    }

    sync_delta_t * delta;
    while ((delta = hb_list_item(pv->stream->delta_list, 0)) != NULL)
    {
        hb_list_rem(pv->stream->delta_list, delta);
        free(delta);
    }
    hb_list_close(&pv->stream->delta_list);
    hb_list_empty(&pv->stream->in_queue);
    hb_list_empty(&pv->stream->scr_delay_queue);
    hb_buffer_list_close(&pv->stream->subtitle.sanitizer.list_current);
    free(pv);
    w->private_data = NULL;
}