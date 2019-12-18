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
typedef  scalar_t__ boolean_t ;
struct TYPE_3__ {void* maxprot; void* initprot; int /*<<< orphan*/  segname; } ;
typedef  TYPE_1__ KXLDSeg ;

/* Variables and functions */
 void* DATA_SEG_PROT ; 
 int /*<<< orphan*/  SEG_TEXT ; 
 void* TEXT_SEG_PROT ; 
 void* VM_PROT_ALL ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void
kxld_seg_set_vm_protections(KXLDSeg *seg, boolean_t strict_protections)
{
    if (strict_protections) {
        if (!strncmp(seg->segname, SEG_TEXT, sizeof(seg->segname))) {
            seg->initprot = TEXT_SEG_PROT;
            seg->maxprot = TEXT_SEG_PROT;
        } else {
            seg->initprot = DATA_SEG_PROT;
            seg->maxprot = DATA_SEG_PROT;
        }
    } else {
        seg->initprot = VM_PROT_ALL;
        seg->maxprot = VM_PROT_ALL;
    }
}