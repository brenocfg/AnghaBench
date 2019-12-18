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
struct qpn_map {int dummy; } ;
struct qib_qpn_table {struct qpn_map* map; } ;

/* Variables and functions */
 int BITS_PER_PAGE ; 

__attribute__((used)) static inline unsigned mk_qpn(struct qib_qpn_table *qpt,
			      struct qpn_map *map, unsigned off)
{
	return (map - qpt->map) * BITS_PER_PAGE + off;
}