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
typedef  int /*<<< orphan*/  u32 ;
struct qib_ibdev {int qp_table_size; int /*<<< orphan*/  qp_rnd; } ;

/* Variables and functions */
 int jhash_1word (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline unsigned qpn_hash(struct qib_ibdev *dev, u32 qpn)
{
	return jhash_1word(qpn, dev->qp_rnd) &
		(dev->qp_table_size - 1);
}