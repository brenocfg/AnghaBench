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
struct hash_ip4_elem {scalar_t__ ip; } ;

/* Variables and functions */

__attribute__((used)) static inline bool
hash_ip4_data_equal(const struct hash_ip4_elem *ip1,
		    const struct hash_ip4_elem *ip2)
{
	return ip1->ip == ip2->ip;
}