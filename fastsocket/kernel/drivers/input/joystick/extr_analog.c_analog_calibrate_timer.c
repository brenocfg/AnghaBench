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
struct gameport {int dummy; } ;
struct analog_port {unsigned int loop; void* speed; struct gameport* gameport; } ;

/* Variables and functions */
 void* DELTA (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  GET_TIME (unsigned int) ; 
 int analog_faketime ; 
 int /*<<< orphan*/  gameport_read (struct gameport*) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  udelay (unsigned int) ; 

__attribute__((used)) static void analog_calibrate_timer(struct analog_port *port)
{
	struct gameport *gameport = port->gameport;
	unsigned int i, t, tx, t1, t2, t3;
	unsigned long flags;

	local_irq_save(flags);
	GET_TIME(t1);
#ifdef FAKE_TIME
	analog_faketime += 830;
#endif
	mdelay(1);
	GET_TIME(t2);
	GET_TIME(t3);
	local_irq_restore(flags);

	port->speed = DELTA(t1, t2) - DELTA(t2, t3);

	tx = ~0;

	for (i = 0; i < 50; i++) {
		local_irq_save(flags);
		GET_TIME(t1);
		for (t = 0; t < 50; t++) { gameport_read(gameport); GET_TIME(t2); }
		GET_TIME(t3);
		local_irq_restore(flags);
		udelay(i);
		t = DELTA(t1, t2) - DELTA(t2, t3);
		if (t < tx) tx = t;
	}

        port->loop = tx / 50;
}