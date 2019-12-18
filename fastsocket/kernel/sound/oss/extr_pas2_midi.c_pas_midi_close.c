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

/* Variables and functions */
 scalar_t__ midi_busy ; 
 int /*<<< orphan*/  pas_remove_intr (int) ; 
 int /*<<< orphan*/  pas_write (int,int) ; 

__attribute__((used)) static void pas_midi_close(int dev)
{

	/*
	 * Reset FIFO pointers, disable intrs
	 */
	pas_write(0x20 | 0x40, 0x178b);

	pas_remove_intr(0x10);
	midi_busy = 0;
}