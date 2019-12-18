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
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__* cothread_t ;

/* Variables and functions */
 int /*<<< orphan*/  CO_SWAP_ASM (scalar_t__*,scalar_t__*) ; 
 uintptr_t above_stack ; 
 scalar_t__ co_active () ; 
 scalar_t__* co_create_ (unsigned int,uintptr_t) ; 
 uintptr_t stack_align ; 
 scalar_t__ state_size ; 

cothread_t co_create( unsigned int size, void (*entry_)( void ) )
{
	uintptr_t entry = (uintptr_t) entry_;
	uint32_t* t = NULL;
	
	/* Be sure main thread was successfully allocated */
	if ( co_active() )
	{
		size += state_size + above_stack + stack_align;
		t = co_create_( size, entry );
	}
	
	if ( t )
	{
		uintptr_t sp;
		int shift;
		
		/* Save current registers into new thread, so that any special ones will
		have proper values when thread is begun */
		CO_SWAP_ASM( t, t );
		
		#if LIBCO_PPCDESC
			/* Get real address */
			entry = (uintptr_t) *(void**) entry;
		#endif
		
		/* Put stack near end of block, and align */
		sp = (uintptr_t) t + size - above_stack;
		sp -= sp % stack_align;
		
		/* On PPC32, we save and restore GPRs as 32 bits. For PPC64, we
		save and restore them as 64 bits, regardless of the size the ABI
		uses. So, we manually write pointers at the proper size. We always
		save and restore at the same address, and since PPC is big-endian,
		we must put the low byte first on PPC32. */
		
		/* If uintptr_t is 32 bits, >>32 is undefined behavior, so we do two shifts
		and don't have to care how many bits uintptr_t is. */
		#if LIBCO_PPC64
			shift = 16;
		#else
			shift = 0;
		#endif
		
		/* Set up so entry will be called on next swap */
		t [8] = (uint32_t) (entry >> shift >> shift);
		t [9] = (uint32_t) entry;
		
		t [10] = (uint32_t) (sp >> shift >> shift); 
		t [11] = (uint32_t) sp;
	}
	
	return t;
}