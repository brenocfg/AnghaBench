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
 int OPEN_READ ; 
 scalar_t__ input_avail () ; 
 int /*<<< orphan*/  midi_input_intr (int /*<<< orphan*/ ,unsigned char) ; 
 int /*<<< orphan*/  my_dev ; 
 int uart6850_opened ; 
 unsigned char uart6850_read () ; 

__attribute__((used)) static void uart6850_input_loop(void)
{
	int count = 10;

	while (count)
	{
		/*
		 * Not timed out
		 */
		if (input_avail())
		{
			unsigned char c = uart6850_read();
			count = 100;
			if (uart6850_opened & OPEN_READ)
				midi_input_intr(my_dev, c);
		}
		else
		{
			while (!input_avail() && count)
				count--;
		}
	}
}