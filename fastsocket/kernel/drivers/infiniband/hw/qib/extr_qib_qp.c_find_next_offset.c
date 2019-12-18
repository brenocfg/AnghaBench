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
struct qpn_map {int /*<<< orphan*/  page; } ;
struct qib_qpn_table {int mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  BITS_PER_PAGE ; 
 unsigned int find_next_zero_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static inline unsigned find_next_offset(struct qib_qpn_table *qpt,
					struct qpn_map *map, unsigned off,
					unsigned n)
{
	if (qpt->mask) {
		off++;
		if (((off & qpt->mask) >> 1) >= n)
			off = (off | qpt->mask) + 2;
	} else
		off = find_next_zero_bit(map->page, BITS_PER_PAGE, off);
	return off;
}