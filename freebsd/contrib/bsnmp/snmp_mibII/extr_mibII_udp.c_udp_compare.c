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
struct udp_index {int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int asn_compare_oid (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
udp_compare(const void *p1, const void *p2)
{
	const struct udp_index *t1 = p1;
	const struct udp_index *t2 = p2;

	return (asn_compare_oid(&t1->index, &t2->index));
}