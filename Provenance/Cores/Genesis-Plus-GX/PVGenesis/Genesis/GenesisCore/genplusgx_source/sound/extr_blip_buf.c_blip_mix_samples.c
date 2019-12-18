#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  buf_t ;
struct TYPE_5__ {int offset; int integrator; } ;
typedef  TYPE_1__ blip_t ;

/* Variables and functions */
 int ARITH_SHIFT (int,int) ; 
 int /*<<< orphan*/  CLAMP (int) ; 
 int /*<<< orphan*/ * SAMPLES (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int bass_shift ; 
 int delta_bits ; 
 int /*<<< orphan*/  remove_samples (TYPE_1__*,int) ; 
 int time_bits ; 

int blip_mix_samples( blip_t* m, short out [], int count)
{
#ifdef BLIP_ASSERT
	assert( count >= 0 );
	
	if ( count > (m->offset >> time_bits) )
		count = m->offset >> time_bits;
	
	if ( count )
#endif
  {
		buf_t const* in  = SAMPLES( m );
		buf_t const* end = in + count;
		int sum = m->integrator;
		do
		{
			/* Eliminate fraction */
			int s = ARITH_SHIFT( sum, delta_bits );
			
			sum += *in++;
			
			/* High-pass filter */
			sum -= s << (delta_bits - bass_shift);

            /* Add current buffer value */
            s += *out;
			
			CLAMP( s );
			
			*out = s;
			out += 2;
		}
		while ( in != end );
		m->integrator = sum;
		
		remove_samples( m, count );
	}
	
	return count;
}