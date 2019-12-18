#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  list_subtitle; } ;
typedef  TYPE_1__ hb_work_private_t ;
struct TYPE_6__ {int /*<<< orphan*/  fifo_in; } ;
typedef  TYPE_2__ hb_subtitle_t ;
typedef  int /*<<< orphan*/  hb_buffer_t ;

/* Variables and functions */
 int /*<<< orphan*/ * hb_buffer_dup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_fifo_push (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int hb_list_count (int /*<<< orphan*/ ) ; 
 TYPE_2__* hb_list_item (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void cc_send_to_decoder(hb_work_private_t *pv, hb_buffer_t *buf)
{
    if (buf == NULL)
        return;

    // if there's more than one decoder for the captions send a copy
    // of the buffer to all.
    hb_subtitle_t *subtitle;
    int ii = 0, n = hb_list_count(pv->list_subtitle);
    while (--n > 0)
    {
        // make a copy of the buf then forward it to the decoder
        hb_buffer_t *cpy = hb_buffer_dup(buf);

        subtitle = hb_list_item(pv->list_subtitle, ii++);
        hb_fifo_push(subtitle->fifo_in, cpy);
    }
    subtitle = hb_list_item(pv->list_subtitle, ii);
    hb_fifo_push( subtitle->fifo_in, buf );
}