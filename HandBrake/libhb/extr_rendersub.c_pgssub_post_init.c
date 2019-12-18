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
typedef  int /*<<< orphan*/  hb_job_t ;
struct TYPE_4__ {int /*<<< orphan*/  sub_list; } ;
typedef  TYPE_1__ hb_filter_private_t ;
struct TYPE_5__ {TYPE_1__* private_data; } ;
typedef  TYPE_2__ hb_filter_object_t ;

/* Variables and functions */
 int /*<<< orphan*/  hb_list_init () ; 

__attribute__((used)) static int pgssub_post_init( hb_filter_object_t * filter, hb_job_t * job )
{
    hb_filter_private_t * pv = filter->private_data;

    pv->sub_list = hb_list_init();

    return 0;
}