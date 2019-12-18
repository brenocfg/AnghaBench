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
typedef  int /*<<< orphan*/  hb_work_private_t ;
struct TYPE_3__ {int /*<<< orphan*/ * private_data; } ;
typedef  TYPE_1__ hb_work_object_t ;

/* Variables and functions */
 int /*<<< orphan*/  closePrivData (int /*<<< orphan*/ **) ; 

__attribute__((used)) static void decavcodecClose( hb_work_object_t * w )
{
    hb_work_private_t * pv = w->private_data;

    if ( pv )
    {
        closePrivData( &pv );
        w->private_data = NULL;
    }
}