#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  extrelocs; } ;
typedef  TYPE_1__ KXLDObject ;
typedef  int /*<<< orphan*/  KXLDArray ;

/* Variables and functions */
 int /*<<< orphan*/  check (TYPE_1__ const*) ; 
 scalar_t__ kxld_object_is_final_image (TYPE_1__ const*) ; 

const KXLDArray  * 
kxld_object_get_extrelocs(const KXLDObject *object)
{
    const KXLDArray *rval = NULL;
    
    check(object);

    if (kxld_object_is_final_image(object)) {
        rval = &object->extrelocs;
    }

    return rval;
}