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
struct ip_set {scalar_t__ ref; char const* name; } ;
typedef  size_t ip_set_id_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 struct ip_set** ip_set_list ; 

const char *
ip_set_name_byindex(ip_set_id_t index)
{
	const struct ip_set *set = ip_set_list[index];

	BUG_ON(set == NULL);
	BUG_ON(set->ref == 0);

	/* Referenced, so it's safe */
	return set->name;
}