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
struct ib_ah_attr {int dummy; } ;
struct qib_ah {struct ib_ah_attr attr; } ;
struct ib_ah {int dummy; } ;

/* Variables and functions */
 struct qib_ah* to_iah (struct ib_ah*) ; 

__attribute__((used)) static int qib_query_ah(struct ib_ah *ibah, struct ib_ah_attr *ah_attr)
{
	struct qib_ah *ah = to_iah(ibah);

	*ah_attr = ah->attr;

	return 0;
}