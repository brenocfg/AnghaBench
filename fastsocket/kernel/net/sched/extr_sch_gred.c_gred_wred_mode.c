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
struct gred_sched {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  GRED_WRED_MODE ; 
 int test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int gred_wred_mode(struct gred_sched *table)
{
	return test_bit(GRED_WRED_MODE, &table->flags);
}