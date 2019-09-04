#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  void* u_long ;
struct TYPE_5__ {void* linkedKextSize; } ;
struct TYPE_6__ {TYPE_1__ split_info; void* output_buffer_size; } ;
typedef  TYPE_2__ KXLDObject ;

/* Variables and functions */
 int /*<<< orphan*/  check (TYPE_2__*) ; 
 scalar_t__ isOldInterface ; 

void
kxld_object_set_linked_object_size(KXLDObject *object, u_long vmsize)
{
    check(object);

    if (isOldInterface) {
        object->output_buffer_size = vmsize;	/* cache this for use later */
    }
    else {
        object->split_info.linkedKextSize = vmsize;
    }
    return;
}