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
typedef  int vm_prot_t ;
typedef  TYPE_1__* vm_map_t ;
typedef  int /*<<< orphan*/  vm_map_offset_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ ppnum_t ;
typedef  int /*<<< orphan*/  pmap_t ;
typedef  int /*<<< orphan*/  mach_vm_size_t ;
typedef  scalar_t__ mach_vm_address_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
struct TYPE_4__ {int /*<<< orphan*/  pmap; } ;

/* Variables and functions */
 unsigned int IODefaultCacheBits (scalar_t__) ; 
 int VM_PROT_READ ; 
 int VM_PROT_WRITE ; 
 unsigned int VM_WIMG_COPYBACK ; 
 unsigned int VM_WIMG_INNERWBACK ; 
 unsigned int VM_WIMG_IO ; 
 unsigned int VM_WIMG_POSTED ; 
 unsigned int VM_WIMG_WCOMB ; 
 unsigned int VM_WIMG_WTHRU ; 
 scalar_t__ atop_64 (scalar_t__) ; 
 unsigned int kIOMapCacheMask ; 
#define  kIOMapCopybackCache 134 
#define  kIOMapCopybackInnerCache 133 
#define  kIOMapDefaultCache 132 
#define  kIOMapInhibitCache 131 
#define  kIOMapPostedWrite 130 
 unsigned int kIOMapReadOnly ; 
#define  kIOMapWriteCombineCache 129 
#define  kIOMapWriteThruCache 128 
 int /*<<< orphan*/  pmap_map_block (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_set_cache_attributes (scalar_t__,unsigned int) ; 
 scalar_t__ round_page_64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_map_set_cache_attr (TYPE_1__*,int /*<<< orphan*/ ) ; 

kern_return_t IOMapPages(vm_map_t map, mach_vm_address_t va, mach_vm_address_t pa,
			mach_vm_size_t length, unsigned int options)
{
    vm_prot_t	 prot;
    unsigned int flags;
    ppnum_t	 pagenum;
    pmap_t 	 pmap = map->pmap;

    prot = (options & kIOMapReadOnly)
		? VM_PROT_READ : (VM_PROT_READ|VM_PROT_WRITE);

    pagenum = (ppnum_t)atop_64(pa);

    switch(options & kIOMapCacheMask ) {			/* What cache mode do we need? */

	case kIOMapDefaultCache:
	default:
	    flags = IODefaultCacheBits(pa);
	    break;

	case kIOMapInhibitCache:
	    flags = VM_WIMG_IO;
	    break;

	case kIOMapWriteThruCache:
	    flags = VM_WIMG_WTHRU;
	    break;

	case kIOMapWriteCombineCache:
	    flags = VM_WIMG_WCOMB;
	    break;

	case kIOMapCopybackCache:
	    flags = VM_WIMG_COPYBACK;
	    break;

	case kIOMapCopybackInnerCache:
	    flags = VM_WIMG_INNERWBACK;
	    break;

	case kIOMapPostedWrite:
	    flags = VM_WIMG_POSTED;
	    break;
    }

    pmap_set_cache_attributes(pagenum, flags);

    vm_map_set_cache_attr(map, (vm_map_offset_t)va);


    // Set up a block mapped area
    return pmap_map_block(pmap, va, pagenum, (uint32_t) atop_64(round_page_64(length)), prot, 0, 0);
}