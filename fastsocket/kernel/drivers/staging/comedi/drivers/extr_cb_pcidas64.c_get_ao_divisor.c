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
 unsigned int get_divisor (unsigned int,unsigned int) ; 

__attribute__((used)) static unsigned int get_ao_divisor(unsigned int ns, unsigned int flags)
{
	return get_divisor(ns, flags) - 2;
}