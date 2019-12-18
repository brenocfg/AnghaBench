#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int ;
typedef  int /*<<< orphan*/  kern_return_t ;
struct TYPE_9__ {scalar_t__ nitems; } ;
struct TYPE_8__ {TYPE_6__ sects; int /*<<< orphan*/  segname; } ;
typedef  TYPE_1__ KXLDSeg ;
typedef  TYPE_1__ KXLDSect ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_FAILURE ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  check (TYPE_1__*) ; 
 int /*<<< orphan*/  finish ; 
 TYPE_1__** kxld_array_get_item (TYPE_6__*,scalar_t__) ; 
 int /*<<< orphan*/  require_action (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int streq_safe (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

kern_return_t
kxld_seg_add_section(KXLDSeg *seg, KXLDSect *sect)
{
    kern_return_t rval = KERN_FAILURE;
    KXLDSect **sectp = NULL;
    u_int i;

    check(seg);
    check(sect);
    require_action(streq_safe(seg->segname, sect->segname, sizeof(seg->segname)),
        finish, rval=KERN_FAILURE);
    
    /* Add the section into the section index */

    for (i = 0; i < seg->sects.nitems; ++i) {
        sectp = kxld_array_get_item(&seg->sects, i);
        if (NULL == *sectp) {
            *sectp = sect;
            break;
        }
    }
    require_action(i < seg->sects.nitems, finish, rval=KERN_FAILURE);

    rval = KERN_SUCCESS;

finish:

    return rval;
}