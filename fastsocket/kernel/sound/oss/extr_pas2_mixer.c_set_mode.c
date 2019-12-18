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
 int /*<<< orphan*/  mix_write (int,int) ; 
 int mode_control ; 

__attribute__((used)) static void
set_mode(int new_mode)
{
	mix_write(0x80 | 0x05, 0x078B);
	mix_write(new_mode, 0x078B);

	mode_control = new_mode;
}