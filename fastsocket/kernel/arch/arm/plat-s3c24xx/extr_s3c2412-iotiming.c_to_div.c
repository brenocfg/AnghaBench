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
 unsigned int DIV_ROUND_UP (unsigned int,unsigned int) ; 

__attribute__((used)) static inline unsigned int to_div(unsigned int cyc_tns, unsigned int clk_tns)
{
	return cyc_tns ? DIV_ROUND_UP(cyc_tns, clk_tns) : 0;
}