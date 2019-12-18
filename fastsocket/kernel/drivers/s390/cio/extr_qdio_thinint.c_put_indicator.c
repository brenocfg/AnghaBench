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
typedef  int /*<<< orphan*/  u32 ;
struct indicator_t {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  count; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 TYPE_1__* q_indicators ; 

__attribute__((used)) static void put_indicator(u32 *addr)
{
	int i;

	if (!addr)
		return;
	i = ((unsigned long)addr - (unsigned long)q_indicators) /
		sizeof(struct indicator_t);
	atomic_dec(&q_indicators[i].count);
}