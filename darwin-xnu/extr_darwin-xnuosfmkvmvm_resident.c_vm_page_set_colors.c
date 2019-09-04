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
 int COLOR_GROUPS_TO_STEAL ; 
 unsigned int DEFAULT_COLORS ; 
 unsigned int MAX_COLORS ; 
 scalar_t__ PE_parse_boot_argn (char*,unsigned int*,int) ; 
 int real_ncpus ; 
 int vm_cache_geometry_colors ; 
 int vm_clump_shift ; 
 int vm_clump_size ; 
 unsigned int vm_color_mask ; 
 int vm_colors ; 
 int vm_free_magazine_refill_limit ; 

__attribute__((used)) static void
vm_page_set_colors( void )
{
	unsigned int	n, override;

#if defined (__x86_64__)	
	/* adjust #colors because we need to color outside the clump boundary */
	vm_cache_geometry_colors >>= vm_clump_shift;
#endif
	if ( PE_parse_boot_argn("colors", &override, sizeof (override)) )		/* colors specified as a boot-arg? */
		n = override;	
	else if ( vm_cache_geometry_colors )			/* do we know what the cache geometry is? */
		n = vm_cache_geometry_colors;
	else	n = DEFAULT_COLORS;				/* use default if all else fails */

	if ( n == 0 )
		n = 1;
	if ( n > MAX_COLORS )
		n = MAX_COLORS;
		
	/* the count must be a power of 2  */
	if ( ( n & (n - 1)) != 0  )
	        n = DEFAULT_COLORS;				/* use default if all else fails */
	
	vm_colors = n;
	vm_color_mask = n - 1;

	vm_free_magazine_refill_limit = vm_colors * COLOR_GROUPS_TO_STEAL;

#if defined (__x86_64__)
        /* adjust for reduction in colors due to clumping and multiple cores */
	if (real_ncpus)
		vm_free_magazine_refill_limit *= (vm_clump_size * real_ncpus);
#endif
}