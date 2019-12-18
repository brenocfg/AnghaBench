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
typedef  int fixed_t ;
struct TYPE_3__ {int offset; int size; int factor; } ;
typedef  TYPE_1__ blip_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int time_bits ; 
 int time_unit ; 

int blip_clocks_needed( const blip_t* m, int samples )
{
	fixed_t needed;
	
#ifdef BLIP_ASSERT
	/* Fails if buffer can't hold that many more samples */
	assert( (samples >= 0) && (((m->offset >> time_bits) + samples) <= m->size) );
#endif

  needed = (fixed_t) samples * time_unit;
	if ( needed < m->offset )
		return 0;
	
	return (needed - m->offset + m->factor - 1) / m->factor;
}