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
typedef  scalar_t__ u_long ;
typedef  int /*<<< orphan*/  u_char ;
typedef  int kxld_addr_t ;
struct TYPE_3__ {int (* allocate_callback ) (scalar_t__,int*,void*) ;int /*<<< orphan*/  kext; } ;
typedef  TYPE_1__ KXLDContext ;
typedef  int KXLDAllocateFlags ;

/* Variables and functions */
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  finish ; 
 int kKxldAllocateWritable ; 
 int /*<<< orphan*/  kKxldLogErr ; 
 int /*<<< orphan*/  kKxldLogLinking ; 
 int kxld_get_effective_page_size () ; 
 int /*<<< orphan*/  kxld_kext_get_vmsize (int /*<<< orphan*/ ,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  kxld_kext_set_linked_object_size (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  kxld_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,void*) ; 
 int /*<<< orphan*/ * kxld_page_alloc_untracked (scalar_t__) ; 
 int /*<<< orphan*/  require (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  require_action (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (scalar_t__,int*,void*) ; 

__attribute__((used)) static u_char *
allocate_kext(KXLDContext *context,
              void *callback_data,
              kxld_addr_t *vmaddr_out,
              u_long *vmsize_out,
              u_char **linked_object_alloc_out)
{
    KXLDAllocateFlags   flags                   = 0;
    kxld_addr_t         vmaddr                  = 0;
    u_long              vmsize                  = 0;
    u_long              header_size             = 0;
    u_char            * linked_object           = NULL;
    
    *linked_object_alloc_out = NULL;
    
    kxld_kext_get_vmsize(context->kext, &header_size, &vmsize);
    
    vmaddr = context->allocate_callback(vmsize, &flags, callback_data);
    require_action(!(vmaddr & (kxld_get_effective_page_size()-1)), finish,
                   kxld_log(kKxldLogLinking, kKxldLogErr,
                            "Load address %p is not page-aligned.",
                            (void *) (uintptr_t) vmaddr));
    
    if (flags & kKxldAllocateWritable) {
        linked_object = (u_char *) (u_long) vmaddr;
    } else {
        linked_object = kxld_page_alloc_untracked(vmsize);
        require(linked_object, finish);
        
        *linked_object_alloc_out = linked_object;
    }
    
    kxld_kext_set_linked_object_size(context->kext, vmsize);
    
    /* Zero out the memory before we fill it.  We fill this buffer in a
     * sparse fashion, and it's simpler to clear it now rather than
     * track and zero any pieces we didn't touch after we've written
     * all of the sections to memory.
     */
    bzero(linked_object, vmsize);
    *vmaddr_out = vmaddr;
    *vmsize_out = vmsize;
    
finish:
    return linked_object;
}