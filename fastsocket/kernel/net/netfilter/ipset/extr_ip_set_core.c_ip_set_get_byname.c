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
 int /*<<< orphan*/  __ip_set_get (size_t) ; 
 struct ip_set** ip_set_list ; 
 size_t ip_set_max ; 

ip_set_id_t
ip_set_get_byname(const char *name, struct ip_set **set)
{
	ip_set_id_t i, index = IPSET_INVALID_ID;
	struct ip_set *s;

	for (i = 0; i < ip_set_max; i++) {
		s = ip_set_list[i];
		if (s != NULL && STREQ(s->name, name)) {
			__ip_set_get(i);
			index = i;
			*set = s;
		}
	}

	return index;
}