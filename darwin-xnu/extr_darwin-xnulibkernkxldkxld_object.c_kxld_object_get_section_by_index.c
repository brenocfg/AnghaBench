#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int ;
struct TYPE_6__ {scalar_t__ nitems; } ;
struct TYPE_5__ {TYPE_3__ sects; } ;
typedef  int /*<<< orphan*/  const KXLDSect ;
typedef  TYPE_1__ KXLDObject ;

/* Variables and functions */
 int /*<<< orphan*/  check (TYPE_1__ const*) ; 
 int /*<<< orphan*/  const* kxld_array_get_item (TYPE_3__*,scalar_t__) ; 

const KXLDSect * 
kxld_object_get_section_by_index(const KXLDObject *object, u_int sectnum)
{
    KXLDSect *sect = NULL;
    
    check(object);

    if (sectnum < object->sects.nitems) {
        sect = kxld_array_get_item(&object->sects, sectnum);
    }

    return sect;
}