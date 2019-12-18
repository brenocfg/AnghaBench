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
#define  CLOCK_DEFAULT 130 
#define  CLOCK_EXT 129 
#define  CLOCK_INT 128 
 int CONTROL_HSS0_CLK_INT ; 
 int CONTROL_HSS1_CLK_INT ; 
 int EINVAL ; 
 int /*<<< orphan*/  output_control () ; 
 int /*<<< orphan*/  set_control (int,int) ; 

__attribute__((used)) static int hss_set_clock(int port, unsigned int clock_type)
{
	int ctrl_int = port ? CONTROL_HSS1_CLK_INT : CONTROL_HSS0_CLK_INT;

	switch (clock_type) {
	case CLOCK_DEFAULT:
	case CLOCK_EXT:
		set_control(ctrl_int, 0);
		output_control();
		return CLOCK_EXT;

	case CLOCK_INT:
		set_control(ctrl_int, 1);
		output_control();
		return CLOCK_INT;

	default:
		return -EINVAL;
	}
}