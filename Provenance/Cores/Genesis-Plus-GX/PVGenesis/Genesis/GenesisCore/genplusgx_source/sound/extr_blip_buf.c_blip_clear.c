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
struct TYPE_4__ {int offset; int factor; int size; scalar_t__ integrator; } ;
typedef  TYPE_1__ blip_t ;

/* Variables and functions */
 int /*<<< orphan*/  SAMPLES (TYPE_1__*) ; 
 int buf_extra ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void blip_clear( blip_t* m )
{
	/* We could set offset to 0, factor/2, or factor-1. 0 is suitable if
	factor is rounded up. factor-1 is suitable if factor is rounded down.
	Since we don't know rounding direction, factor/2 accommodates either,
	with the slight loss of showing an error in half the time. Since for
	a 64-bit factor this is years, the halving isn't a problem. */
	
	m->offset     = m->factor / 2;
	m->integrator = 0;
	memset( SAMPLES( m ), 0, (m->size + buf_extra) * sizeof (buf_t) );
}