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
struct hw {int (* have_digit_io_switch ) (struct hw*) ;} ;
struct ct_atc {struct hw* hw; } ;

/* Variables and functions */
 int stub1 (struct hw*) ; 

__attribute__((used)) static int atc_have_digit_io_switch(struct ct_atc *atc)
{
	struct hw *hw = atc->hw;

	return hw->have_digit_io_switch(hw);
}