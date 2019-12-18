#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct TYPE_6__* cc608; struct TYPE_6__* data608; } ;
typedef  TYPE_1__ hb_work_private_t ;
struct TYPE_7__ {TYPE_1__* private_data; } ;
typedef  TYPE_2__ hb_work_object_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  general_608_close (TYPE_1__*) ; 

__attribute__((used)) static void decccClose( hb_work_object_t * w )
{
    hb_work_private_t * pv = w->private_data;

    if (pv)
    {
        general_608_close( pv->cc608 );
        free( pv->cc608->data608 );
        free( pv->cc608 );
    }
    free( w->private_data );
}