#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  override ;

/* Variables and functions */
 int DEFAULT_CLUMP_SIZE ; 
 int MAX_CLUMP_SIZE ; 
 scalar_t__ PE_parse_boot_argn (char*,unsigned int*,int) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int vm_clump_mask ; 
 int vm_clump_promote_threshold ; 
 scalar_t__ vm_clump_shift ; 
 int vm_clump_size ; 

__attribute__((used)) static void
vm_page_setup_clump( void )
{
    unsigned int override, n;

    vm_clump_size = DEFAULT_CLUMP_SIZE;
    if ( PE_parse_boot_argn("clump_size", &override, sizeof (override)) ) vm_clump_size = override;

    if(vm_clump_size > MAX_CLUMP_SIZE) panic("vm_page_setup_clump:: clump_size is too large!");
    if(vm_clump_size < 1) panic("vm_page_setup_clump:: clump_size must be >= 1");
    if((vm_clump_size & (vm_clump_size-1)) != 0)  panic("vm_page_setup_clump:: clump_size must be a power of 2");

    vm_clump_promote_threshold = vm_clump_size;
    vm_clump_mask = vm_clump_size - 1;
    for(vm_clump_shift=0, n=vm_clump_size; n>1; n>>=1, vm_clump_shift++);

#if DEVELOPMENT || DEBUG
    bzero(vm_clump_stats, sizeof(vm_clump_stats));
    vm_clump_allocs = vm_clump_inserts = vm_clump_inrange = vm_clump_promotes = 0;
#endif  /*  if DEVELOPMENT || DEBUG */
}