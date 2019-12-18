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
typedef  double fixed_t ;
struct TYPE_3__ {double factor; } ;
typedef  TYPE_1__ blip_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 double time_unit ; 

void blip_set_rates( blip_t* m, double clock_rate, double sample_rate )
{
	double factor = time_unit * sample_rate / clock_rate;
	m->factor = (fixed_t) factor;
	
#ifdef BLIP_ASSERT
	/* Fails if clock_rate exceeds maximum, relative to sample_rate */
	assert( 0 <= factor - m->factor && factor - m->factor < 1 );
#endif
  
/* Avoid requiring math.h. Equivalent to
	m->factor = (int) ceil( factor ) */
	if ( m->factor < factor )
		m->factor++;
	
	/* At this point, factor is most likely rounded up, but could still
	have been rounded down in the floating-point calculation. */
}