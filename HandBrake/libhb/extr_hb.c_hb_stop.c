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
struct TYPE_4__ {int work_die; int /*<<< orphan*/  work_error; } ;
typedef  TYPE_1__ hb_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  HB_ERROR_CANCELED ; 
 int /*<<< orphan*/  hb_resume (TYPE_1__*) ; 

void hb_stop( hb_handle_t * h )
{
    h->work_error = HB_ERROR_CANCELED;
    h->work_die   = 1;
    hb_resume( h );
}