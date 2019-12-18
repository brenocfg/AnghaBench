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
 scalar_t__ B1_INSTAT ; 
 int inb (scalar_t__) ; 

__attribute__((used)) static inline int b1_rx_full(unsigned int base)
{
	return inb(base + B1_INSTAT) & 0x1;
}