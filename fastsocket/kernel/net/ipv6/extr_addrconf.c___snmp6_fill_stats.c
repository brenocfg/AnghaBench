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
typedef  int /*<<< orphan*/  u64 ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  put_unaligned (int,int /*<<< orphan*/ *) ; 
 int snmp_fold_field (void**,int) ; 

__attribute__((used)) static inline void __snmp6_fill_stats(u64 *stats, void **mib, int items,
				      int bytes)
{
	int i;
	int pad = bytes - sizeof(u64) * items;
	BUG_ON(pad < 0);

	/* Use put_unaligned() because stats may not be aligned for u64. */
	put_unaligned(items, &stats[0]);
	for (i = 1; i < items; i++)
		put_unaligned(snmp_fold_field(mib, i), &stats[i]);

	memset(&stats[items], 0, pad);
}