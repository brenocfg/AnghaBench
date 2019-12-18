#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned long* pio_write_status_addr; unsigned long pio_write_status_val; } ;

/* Variables and functions */
 unsigned long SH_PIO_WRITE_STATUS_PENDING_WRITE_COUNT_MASK ; 
 unsigned long SH_PIO_WRITE_STATUS_WRITE_DEADLOCK_MASK ; 
 int /*<<< orphan*/  cpu_relax () ; 
 TYPE_1__* pda ; 

__attribute__((used)) static inline unsigned long wait_piowc(void)
{
	volatile unsigned long *piows;
	unsigned long zeroval, ws;

	piows = pda->pio_write_status_addr;
	zeroval = pda->pio_write_status_val;
	do {
		cpu_relax();
	} while (((ws = *piows) & SH_PIO_WRITE_STATUS_PENDING_WRITE_COUNT_MASK) != zeroval);
	return (ws & SH_PIO_WRITE_STATUS_WRITE_DEADLOCK_MASK) != 0;
}