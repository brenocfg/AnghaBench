#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {TYPE_5__* cc608; } ;
typedef  TYPE_2__ hb_work_private_t ;
struct TYPE_14__ {TYPE_2__* private_data; } ;
typedef  TYPE_3__ hb_work_object_t ;
struct TYPE_12__ {int flags; int /*<<< orphan*/  scr_sequence; int /*<<< orphan*/  start; } ;
struct TYPE_15__ {int /*<<< orphan*/  size; int /*<<< orphan*/  data; TYPE_1__ s; } ;
typedef  TYPE_4__ hb_buffer_t ;
struct TYPE_16__ {int /*<<< orphan*/  list; int /*<<< orphan*/  last_scr_sequence; int /*<<< orphan*/  last_pts; } ;

/* Variables and functions */
 int HB_BUF_FLAG_EOF ; 
 int HB_WORK_DONE ; 
 int HB_WORK_OK ; 
 int /*<<< orphan*/  handle_end_of_data (TYPE_5__*) ; 
 int /*<<< orphan*/  hb_buffer_list_append (int /*<<< orphan*/ *,TYPE_4__*) ; 
 TYPE_4__* hb_buffer_list_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  process608 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*) ; 

__attribute__((used)) static int decccWork( hb_work_object_t * w, hb_buffer_t ** buf_in,
               hb_buffer_t ** buf_out )
{
    hb_work_private_t * pv = w->private_data;
    hb_buffer_t * in = *buf_in;

    if (in->s.flags & HB_BUF_FLAG_EOF)
    {
        /* EOF on input stream - send it downstream & say that we're done */
        handle_end_of_data(pv->cc608);
        /*
         * Grab any pending buffer and output them with the EOF on the end
         */
        *buf_in = NULL;
        hb_buffer_list_append(&pv->cc608->list, in);
        *buf_out = hb_buffer_list_clear(&pv->cc608->list);
        return HB_WORK_DONE;
    }

    pv->cc608->last_pts = in->s.start;
    pv->cc608->last_scr_sequence = in->s.scr_sequence;
    process608(in->data, in->size, pv->cc608);

    /*
     * If there is one waiting then pass it on
     */
    *buf_out = hb_buffer_list_clear(&pv->cc608->list);
    return HB_WORK_OK;
}