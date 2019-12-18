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
 int SERIAL_CONS_OPS ; 
 int cons_ops_index ; 

int
switch_to_serial_console(void)
{
	int old_cons_ops = cons_ops_index;
	cons_ops_index = SERIAL_CONS_OPS;
	return old_cons_ops;
}