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
typedef  int buf_t ;
struct TYPE_4__ {unsigned int factor; unsigned int offset; size_t size; } ;
typedef  TYPE_1__ blip_t ;

/* Variables and functions */
 int* SAMPLES (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 unsigned int delta_bits ; 
 int delta_unit ; 
 size_t end_frame_extra ; 
 unsigned int frac_bits ; 
 unsigned int pre_shift ; 

void blip_add_delta_fast( blip_t* m, unsigned time, int delta )
{
	unsigned fixed = (unsigned) ((time * m->factor + m->offset) >> pre_shift);
	buf_t* out = SAMPLES( m ) + (fixed >> frac_bits);
	
	int interp = fixed >> (frac_bits - delta_bits) & (delta_unit - 1);
	int delta2 = delta * interp;
	
#ifdef BLIP_ASSERT
  /* Fails if buffer size was exceeded */
	assert( out <= &SAMPLES( m ) [m->size + end_frame_extra] );
#endif
  
	out [7] += delta * delta_unit - delta2;
	out [8] += delta2;
}