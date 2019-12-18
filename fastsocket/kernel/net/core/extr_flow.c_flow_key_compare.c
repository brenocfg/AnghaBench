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
struct flowi {int dummy; } ;
typedef  int /*<<< orphan*/  flow_compare_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 

__attribute__((used)) static int flow_key_compare(struct flowi *key1, struct flowi *key2)
{
	flow_compare_t *k1, *k1_lim, *k2;
	const int n_elem = sizeof(struct flowi) / sizeof(flow_compare_t);

	BUILD_BUG_ON(sizeof(struct flowi) % sizeof(flow_compare_t));

	k1 = (flow_compare_t *) key1;
	k1_lim = k1 + n_elem;

	k2 = (flow_compare_t *) key2;

	do {
		if (*k1++ != *k2++)
			return 1;
	} while (k1 < k1_lim);

	return 0;
}