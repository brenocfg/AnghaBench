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
struct TYPE_3__ {int /*<<< orphan*/  work_error; } ;
typedef  TYPE_1__ hb_handle_t ;
typedef  int /*<<< orphan*/  hb_error_code ;

/* Variables and functions */

void hb_set_work_error( hb_handle_t * h, hb_error_code err )
{
    h->work_error = err;
}