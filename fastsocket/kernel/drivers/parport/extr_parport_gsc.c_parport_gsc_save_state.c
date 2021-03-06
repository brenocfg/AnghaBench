#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  ctr; } ;
struct TYPE_4__ {TYPE_1__ pc; } ;
struct parport_state {TYPE_2__ u; } ;
struct parport {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONTROL (struct parport*) ; 
 int /*<<< orphan*/  parport_readb (int /*<<< orphan*/ ) ; 

void parport_gsc_save_state(struct parport *p, struct parport_state *s)
{
	s->u.pc.ctr = parport_readb (CONTROL (p));
}