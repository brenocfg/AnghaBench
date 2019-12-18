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
struct TYPE_5__ {int splice_list_size; TYPE_1__* splice_list; } ;
typedef  TYPE_2__ hb_work_private_t ;
typedef  int /*<<< orphan*/  hb_buffer_list_t ;
struct TYPE_4__ {int id; int /*<<< orphan*/  list; } ;

/* Variables and functions */

__attribute__((used)) static hb_buffer_list_t * get_splice_list(hb_work_private_t * r, int id)
{
    int ii;

    for (ii = 0; ii < r->splice_list_size; ii++)
    {
        if (r->splice_list[ii].id == id)
        {
            return &r->splice_list[ii].list;
        }
    }
    return NULL;
}