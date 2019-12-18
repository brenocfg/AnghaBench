#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct hw {unsigned int (* get_wc ) (struct hw*) ;} ;
struct ct_timer {TYPE_1__* atc; } ;
struct TYPE_2__ {struct hw* hw; } ;

/* Variables and functions */
 unsigned int stub1 (struct hw*) ; 

__attribute__((used)) static inline unsigned int ct_xfitimer_get_wc(struct ct_timer *atimer)
{
	struct hw *hw = atimer->atc->hw;
	return hw->get_wc(hw);
}