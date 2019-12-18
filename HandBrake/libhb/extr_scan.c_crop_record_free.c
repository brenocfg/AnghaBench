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
struct TYPE_4__ {struct TYPE_4__* r; struct TYPE_4__* l; struct TYPE_4__* b; struct TYPE_4__* t; } ;
typedef  TYPE_1__ crop_record_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 

__attribute__((used)) static void crop_record_free( crop_record_t *crops )
{
    free( crops->t );
    free( crops->b );
    free( crops->l );
    free( crops->r );
    free( crops );
}