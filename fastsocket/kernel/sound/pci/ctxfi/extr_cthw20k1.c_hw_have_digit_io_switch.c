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
struct hw {scalar_t__ model; } ;

/* Variables and functions */
 scalar_t__ CTSB073X ; 
 scalar_t__ CTUAA ; 

__attribute__((used)) static int hw_have_digit_io_switch(struct hw *hw)
{
	/* SB073x and Vista compatible cards have no digit IO switch */
	return !(hw->model == CTSB073X || hw->model == CTUAA);
}