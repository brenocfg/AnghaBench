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
typedef  int boolean_t ;

/* Variables and functions */
 scalar_t__ SERIAL_CONS_OPS ; 
 scalar_t__ cons_ops_index ; 

boolean_t
console_is_serial(void)
{
	return (cons_ops_index == SERIAL_CONS_OPS);
}