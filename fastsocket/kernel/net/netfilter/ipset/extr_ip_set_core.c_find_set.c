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
struct ip_set {int dummy; } ;
typedef  size_t ip_set_id_t ;

/* Variables and functions */
 size_t IPSET_INVALID_ID ; 
 size_t find_set_id (char const*) ; 
 struct ip_set** ip_set_list ; 

__attribute__((used)) static inline struct ip_set *
find_set(const char *name)
{
	ip_set_id_t index = find_set_id(name);

	return index == IPSET_INVALID_ID ? NULL : ip_set_list[index];
}