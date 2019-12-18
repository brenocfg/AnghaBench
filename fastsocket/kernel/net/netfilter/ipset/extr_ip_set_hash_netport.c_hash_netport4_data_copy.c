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
struct hash_netport4_elem {int /*<<< orphan*/  cidr; int /*<<< orphan*/  proto; int /*<<< orphan*/  port; int /*<<< orphan*/  ip; } ;

/* Variables and functions */

__attribute__((used)) static inline void
hash_netport4_data_copy(struct hash_netport4_elem *dst,
			const struct hash_netport4_elem *src)
{
	dst->ip = src->ip;
	dst->port = src->port;
	dst->proto = src->proto;
	dst->cidr = src->cidr;
}