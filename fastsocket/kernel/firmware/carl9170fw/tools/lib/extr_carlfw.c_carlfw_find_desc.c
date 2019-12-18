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
typedef  int /*<<< orphan*/  uint8_t ;
struct carlfw_list_entry {int dummy; } ;
struct carlfw {int dummy; } ;

/* Variables and functions */
 void* carlfw_entry_to_desc (struct carlfw_list_entry*) ; 
 struct carlfw_list_entry* carlfw_find_entry (struct carlfw*,int /*<<< orphan*/  const*,unsigned int const,int /*<<< orphan*/  const) ; 

void *carlfw_find_desc(struct carlfw *fw,
		       const uint8_t descid[4],
		       const unsigned int len,
		       const uint8_t compatible_revision)
{
	struct carlfw_list_entry *tmp;

	tmp = carlfw_find_entry(fw, descid, len, compatible_revision);

	return tmp ? carlfw_entry_to_desc(tmp) : NULL;
}