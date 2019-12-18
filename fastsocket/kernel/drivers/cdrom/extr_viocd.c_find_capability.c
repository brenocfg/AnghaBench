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
struct capability_entry {int capability; scalar_t__ type; } ;

/* Variables and functions */
 struct capability_entry* capability_table ; 
 int /*<<< orphan*/  strncmp (scalar_t__,char const*,int) ; 

__attribute__((used)) static int find_capability(const char *type)
{
	struct capability_entry *entry;

	for(entry = capability_table; entry->type; ++entry)
		if(!strncmp(entry->type, type, 4))
			break;
	return entry->capability;
}