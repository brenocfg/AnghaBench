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
typedef  int /*<<< orphan*/  u_long ;
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_5__ {int /*<<< orphan*/ * linkedKext; int /*<<< orphan*/  linkedKextSize; scalar_t__ vmaddr_TEXT; scalar_t__ vmaddr_LINKEDIT; } ;
typedef  TYPE_1__ splitKextLinkInfo ;
typedef  int /*<<< orphan*/  kern_return_t ;
struct TYPE_6__ {int /*<<< orphan*/  kext; } ;
typedef  TYPE_2__ KXLDContext ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_FAILURE ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  SEG_LINKEDIT ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  finish ; 
 scalar_t__ isSplitKext ; 
 int /*<<< orphan*/  kxld_kext_get_vmsize (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kxld_kext_get_vmsize_for_seg_by_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kxld_page_alloc_untracked (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  require (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static kern_return_t
allocate_split_kext(KXLDContext *context, splitKextLinkInfo * link_info)
{
    kern_return_t       rval                    = KERN_FAILURE;
    u_long              vmsize                  = 0;
    u_long              header_size             = 0;
    u_char            * linked_object           = NULL;
    
    kxld_kext_get_vmsize(context->kext, &header_size, &vmsize);
    
    if (isSplitKext) {
        /* get __LINKEDIT vmsize */
        kxld_kext_get_vmsize_for_seg_by_name(context->kext, SEG_LINKEDIT, &vmsize);
        // add in the gaps
        vmsize += (link_info->vmaddr_LINKEDIT - link_info->vmaddr_TEXT);
    }
    link_info->linkedKextSize = vmsize;
    
    linked_object = kxld_page_alloc_untracked(link_info->linkedKextSize);
    require(linked_object, finish);
    link_info->linkedKext = linked_object;

    bzero(linked_object, vmsize);
    rval = KERN_SUCCESS;

finish:
    return rval;
}