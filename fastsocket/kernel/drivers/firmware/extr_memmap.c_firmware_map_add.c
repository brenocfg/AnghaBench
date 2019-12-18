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
typedef  int /*<<< orphan*/  u64 ;
struct firmware_map_entry {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int firmware_map_add_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,struct firmware_map_entry*) ; 
 struct firmware_map_entry* kmalloc (int,int /*<<< orphan*/ ) ; 

int firmware_map_add(u64 start, u64 end, const char *type)
{
	struct firmware_map_entry *entry;

	entry = kmalloc(sizeof(struct firmware_map_entry), GFP_ATOMIC);
	if (!entry)
		return -ENOMEM;

	return firmware_map_add_entry(start, end, type, entry);
}