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
typedef  int u32 ;
struct qpn_map {int /*<<< orphan*/  n_free; int /*<<< orphan*/  page; } ;
struct ipath_qp_table {int last; int nmaps; struct qpn_map* map; } ;
typedef  enum ib_qp_type { ____Placeholder_ib_qp_type } ib_qp_type ;

/* Variables and functions */
 int BITS_PER_PAGE ; 
 int BITS_PER_PAGE_MASK ; 
 int EBUSY ; 
 int ENOMEM ; 
 int IB_QPT_GSI ; 
 int IB_QPT_SMI ; 
 int QPNMAP_ENTRIES ; 
 int QPN_MAX ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int find_next_offset (struct qpn_map*,int) ; 
 int /*<<< orphan*/  get_map_page (struct ipath_qp_table*,struct qpn_map*) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int mk_qpn (struct ipath_qp_table*,struct qpn_map*,int) ; 
 int /*<<< orphan*/  test_and_set_bit (int,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int alloc_qpn(struct ipath_qp_table *qpt, enum ib_qp_type type)
{
	u32 i, offset, max_scan, qpn;
	struct qpn_map *map;
	u32 ret = -1;

	if (type == IB_QPT_SMI)
		ret = 0;
	else if (type == IB_QPT_GSI)
		ret = 1;

	if (ret != -1) {
		map = &qpt->map[0];
		if (unlikely(!map->page)) {
			get_map_page(qpt, map);
			if (unlikely(!map->page)) {
				ret = -ENOMEM;
				goto bail;
			}
		}
		if (!test_and_set_bit(ret, map->page))
			atomic_dec(&map->n_free);
		else
			ret = -EBUSY;
		goto bail;
	}

	qpn = qpt->last + 1;
	if (qpn >= QPN_MAX)
		qpn = 2;
	offset = qpn & BITS_PER_PAGE_MASK;
	map = &qpt->map[qpn / BITS_PER_PAGE];
	max_scan = qpt->nmaps - !offset;
	for (i = 0;;) {
		if (unlikely(!map->page)) {
			get_map_page(qpt, map);
			if (unlikely(!map->page))
				break;
		}
		if (likely(atomic_read(&map->n_free))) {
			do {
				if (!test_and_set_bit(offset, map->page)) {
					atomic_dec(&map->n_free);
					qpt->last = qpn;
					ret = qpn;
					goto bail;
				}
				offset = find_next_offset(map, offset);
				qpn = mk_qpn(qpt, map, offset);
				/*
				 * This test differs from alloc_pidmap().
				 * If find_next_offset() does find a zero
				 * bit, we don't need to check for QPN
				 * wrapping around past our starting QPN.
				 * We just need to be sure we don't loop
				 * forever.
				 */
			} while (offset < BITS_PER_PAGE && qpn < QPN_MAX);
		}
		/*
		 * In order to keep the number of pages allocated to a
		 * minimum, we scan the all existing pages before increasing
		 * the size of the bitmap table.
		 */
		if (++i > max_scan) {
			if (qpt->nmaps == QPNMAP_ENTRIES)
				break;
			map = &qpt->map[qpt->nmaps++];
			offset = 0;
		} else if (map < &qpt->map[qpt->nmaps]) {
			++map;
			offset = 0;
		} else {
			map = &qpt->map[0];
			offset = 2;
		}
		qpn = mk_qpn(qpt, map, offset);
	}

	ret = -ENOMEM;

bail:
	return ret;
}