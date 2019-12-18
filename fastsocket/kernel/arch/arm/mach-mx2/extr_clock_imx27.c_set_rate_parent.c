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
struct clk {TYPE_1__* parent; } ;
struct TYPE_2__ {int (* set_rate ) (TYPE_1__*,unsigned long) ;} ;

/* Variables and functions */
 int stub1 (TYPE_1__*,unsigned long) ; 

__attribute__((used)) static int set_rate_parent(struct clk *clk, unsigned long rate)
{
	return clk->parent->set_rate(clk->parent, rate);
}