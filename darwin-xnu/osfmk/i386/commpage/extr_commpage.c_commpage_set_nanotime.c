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
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_4__ {scalar_t__ nt_generation; scalar_t__ nt_ns_base; scalar_t__ nt_shift; scalar_t__ nt_scale; scalar_t__ nt_tsc_base; } ;
typedef  TYPE_1__ commpage_time_data ;

/* Variables and functions */
 int _cpu_capabilities ; 
 int kSlow ; 
 int /*<<< orphan*/  panic (char*) ; 
 TYPE_1__* time_data32 ; 
 TYPE_1__* time_data64 ; 

void
commpage_set_nanotime(
	uint64_t	tsc_base,
	uint64_t	ns_base,
	uint32_t	scale,
	uint32_t	shift )
{
	commpage_time_data	*p32 = time_data32;
	commpage_time_data	*p64 = time_data64;
	static uint32_t	generation = 0;
	uint32_t	next_gen;
	
	if (p32 == NULL)		/* have commpages been allocated yet? */
		return;
		
	if ( generation != p32->nt_generation )
		panic("nanotime trouble 1");	/* possibly not serialized */
	if ( ns_base < p32->nt_ns_base )
		panic("nanotime trouble 2");
	if ((shift != 0) && ((_cpu_capabilities & kSlow)==0) )
		panic("nanotime trouble 3");
		
	next_gen = ++generation;
	if (next_gen == 0)
		next_gen = ++generation;
	
	p32->nt_generation = 0;		/* mark invalid, so commpage won't try to use it */
	p64->nt_generation = 0;
	
	p32->nt_tsc_base = tsc_base;
	p64->nt_tsc_base = tsc_base;
	
	p32->nt_ns_base = ns_base;
	p64->nt_ns_base = ns_base;
	
	p32->nt_scale = scale;
	p64->nt_scale = scale;
	
	p32->nt_shift = shift;
	p64->nt_shift = shift;
	
	p32->nt_generation = next_gen;	/* mark data as valid */
	p64->nt_generation = next_gen;
}