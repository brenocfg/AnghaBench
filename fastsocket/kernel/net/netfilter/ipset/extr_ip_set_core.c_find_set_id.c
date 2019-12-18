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
struct ip_set {int /*<<< orphan*/  name; } ;
typedef  size_t ip_set_id_t ;

/* Variables and functions */
 size_t IPSET_INVALID_ID ; 
 scalar_t__ STREQ (int /*<<< orphan*/ ,char const*) ; 
 struct ip_set** ip_set_list ; 
 size_t ip_set_max ; 

__attribute__((used)) static ip_set_id_t
find_set_id(const char *name)
{
	ip_set_id_t i, index = IPSET_INVALID_ID;
	const struct ip_set *set;

	for (i = 0; index == IPSET_INVALID_ID && i < ip_set_max; i++) {
		set = ip_set_list[i];
		if (set != NULL && STREQ(set->name, name))
			index = i;
	}
	return index;
}