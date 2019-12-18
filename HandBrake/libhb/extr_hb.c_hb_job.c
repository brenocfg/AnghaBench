#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  hb_job_t ;
struct TYPE_3__ {int /*<<< orphan*/  jobs; } ;
typedef  TYPE_1__ hb_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/ * hb_list_item (int /*<<< orphan*/ ,int) ; 

hb_job_t * hb_job( hb_handle_t * h, int i )
{
    return hb_list_item( h->jobs, i );
}