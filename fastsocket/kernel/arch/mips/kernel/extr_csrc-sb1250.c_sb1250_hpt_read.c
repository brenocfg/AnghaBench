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
struct clocksource {int dummy; } ;
typedef  scalar_t__ cycle_t ;

/* Variables and functions */
 int /*<<< orphan*/  A_SCD_TIMER_REGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int G_SCD_TIMER_CNT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IOADDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  R_SCD_TIMER_CNT ; 
 int /*<<< orphan*/  SB1250_HPT_NUM ; 
 scalar_t__ SB1250_HPT_VALUE ; 
 int /*<<< orphan*/  __raw_readq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static cycle_t sb1250_hpt_read(struct clocksource *cs)
{
	unsigned int count;

	count = G_SCD_TIMER_CNT(__raw_readq(IOADDR(A_SCD_TIMER_REGISTER(SB1250_HPT_NUM, R_SCD_TIMER_CNT))));

	return SB1250_HPT_VALUE - count;
}