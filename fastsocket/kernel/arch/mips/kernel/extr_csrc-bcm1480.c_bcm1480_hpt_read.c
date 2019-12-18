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
typedef  int /*<<< orphan*/  cycle_t ;

/* Variables and functions */
 int /*<<< orphan*/  A_SCD_ZBBUS_CYCLE_COUNT ; 
 int /*<<< orphan*/  IOADDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_readq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static cycle_t bcm1480_hpt_read(struct clocksource *cs)
{
	return (cycle_t) __raw_readq(IOADDR(A_SCD_ZBBUS_CYCLE_COUNT));
}