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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  co_swap_asm ; 
 void* libco_ppc_code ; 
 scalar_t__ malloc (unsigned int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void*,int) ; 

__attribute__((used)) static uint32_t* co_create_( unsigned size, uintptr_t entry )
{
	uint32_t* t = (uint32_t*) malloc( size );
	
	(void) entry;
	
	#if LIBCO_PPCDESC
		if ( t )
		{
			/* Copy entry's descriptor */
			memcpy( t, (void*) entry, sizeof (void*) * 3 );
			
			/* Set function pointer to swap routine */
			#ifdef LIBCO_PPC_ASM
				*(const void**) t = *(void**) &co_swap_asm;
			#else
				*(const void**) t = libco_ppc_code;
			#endif
		}
	#endif
	
	return t;
}