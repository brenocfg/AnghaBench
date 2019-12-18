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
 int /*<<< orphan*/  wb977_device_select (int) ; 
 int /*<<< orphan*/  wb977_wb (int,int) ; 

__attribute__((used)) static inline void wb977_init_printer(void)
{
	wb977_device_select(1);

	/*
	 * mode 1 == EPP
	 */
	wb977_wb(0xf0, 0x01);
}