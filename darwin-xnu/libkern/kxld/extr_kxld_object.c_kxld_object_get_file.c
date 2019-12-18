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
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_5__ {int /*<<< orphan*/ * kextExecutable; } ;
struct TYPE_6__ {TYPE_1__ split_info; int /*<<< orphan*/ * file; } ;
typedef  TYPE_2__ KXLDObject ;

/* Variables and functions */
 int /*<<< orphan*/  check (TYPE_2__ const*) ; 
 scalar_t__ isOldInterface ; 

const u_char *
kxld_object_get_file(const KXLDObject *object)
{
    const u_char *my_file;
    
    check(object);

    if (isOldInterface) {
        my_file = object->file;
    }
    else {
        my_file = object->split_info.kextExecutable;
    }
    
    return my_file;
}