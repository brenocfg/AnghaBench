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
struct TYPE_2__ {int /*<<< orphan*/  p1; int /*<<< orphan*/  p0; } ;

/* Variables and functions */
 unsigned long HZ ; 
 TYPE_1__ etr_eacr ; 
 scalar_t__ etr_port0_uptodate ; 
 scalar_t__ etr_port1_uptodate ; 
 int /*<<< orphan*/  etr_timer ; 
 unsigned long long etr_tolec ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void etr_set_tolec_timeout(unsigned long long now)
{
	unsigned long micros;

	if ((!etr_eacr.p0 || etr_port0_uptodate) &&
	    (!etr_eacr.p1 || etr_port1_uptodate))
		return;
	micros = (now > etr_tolec) ? ((now - etr_tolec) >> 12) : 0;
	micros = (micros > 1600000) ? 0 : 1600000 - micros;
	mod_timer(&etr_timer, jiffies + (micros * HZ) / 1000000 + 1);
}