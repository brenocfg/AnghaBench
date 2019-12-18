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
typedef  int /*<<< orphan*/  buf_t ;
struct TYPE_4__ {int factor; int size; } ;
typedef  TYPE_1__ blip_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  blip_clear (TYPE_1__*) ; 
 int blip_max_ratio ; 
 int buf_extra ; 
 int /*<<< orphan*/  check_assumptions () ; 
 scalar_t__ malloc (int) ; 
 int time_unit ; 

blip_t* blip_new( int size )
{
	blip_t* m;
#ifdef BLIP_ASSERT
	assert( size >= 0 );
#endif
  
	m = (blip_t*) malloc( sizeof *m + (size + buf_extra) * sizeof (buf_t) );
	if ( m )
	{
		m->factor = time_unit / blip_max_ratio;
		m->size   = size;
		blip_clear( m );
#ifdef BLIP_ASSERT
		check_assumptions();
#endif
  }
	return m;
}