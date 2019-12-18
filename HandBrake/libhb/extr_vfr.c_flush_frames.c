#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  frame_rate_list; } ;
typedef  TYPE_1__ hb_filter_private_t ;
typedef  int /*<<< orphan*/  hb_buffer_t ;
typedef  int /*<<< orphan*/  hb_buffer_list_t ;

/* Variables and functions */
 int /*<<< orphan*/  adjust_frame_rate (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_buffer_list_append (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * hb_buffer_list_clear (int /*<<< orphan*/ *) ; 
 scalar_t__ hb_list_count (int /*<<< orphan*/ ) ; 

__attribute__((used)) static hb_buffer_t * flush_frames(hb_filter_private_t * pv)
{
    hb_buffer_list_t list;

    hb_buffer_list_clear(&list);
    while (hb_list_count(pv->frame_rate_list) > 0)
    {
        hb_buffer_list_append(&list, adjust_frame_rate(pv, NULL));
    }

    return hb_buffer_list_clear(&list);
}