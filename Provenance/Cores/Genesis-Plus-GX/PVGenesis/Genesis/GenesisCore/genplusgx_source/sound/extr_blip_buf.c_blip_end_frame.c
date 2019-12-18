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
struct TYPE_3__ {unsigned int offset; unsigned int factor; int size; } ;
typedef  TYPE_1__ blip_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int time_bits ; 

void blip_end_frame( blip_t* m, unsigned t )
{
	m->offset += t * m->factor;
	
#ifdef BLIP_ASSERT
	/* Fails if buffer size was exceeded */
  assert( (m->offset >> time_bits) <= m->size );
#endif
}