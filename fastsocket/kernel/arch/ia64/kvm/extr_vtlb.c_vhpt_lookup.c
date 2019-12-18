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
typedef  scalar_t__ u64 ;
struct thash_data {scalar_t__ etag; } ;

/* Variables and functions */
 scalar_t__ ia64_thash (scalar_t__) ; 
 scalar_t__ ia64_ttag (scalar_t__) ; 

struct thash_data *vhpt_lookup(u64 va)
{
	struct thash_data *head;
	u64 tag;

	head = (struct thash_data *)ia64_thash(va);
	tag = ia64_ttag(va);
	if (head->etag == tag)
		return head;
	return NULL;
}