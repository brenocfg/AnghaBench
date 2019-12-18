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
typedef  int /*<<< orphan*/  u32 ;
struct gameport {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int mp_io (struct gameport*,int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int multiport_io(struct gameport* gameport, int sendflags, int sendcode, u32 *packet)
{
	int status;
	unsigned long flags;

	local_irq_save(flags);
	status = mp_io(gameport, sendflags, sendcode, packet);
	local_irq_restore(flags);

	return status;
}