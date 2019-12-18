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
struct fw_descriptor {scalar_t__ immediate; int /*<<< orphan*/  link; } ;

/* Variables and functions */
 int /*<<< orphan*/  card_mutex ; 
 int /*<<< orphan*/  config_rom_length ; 
 int /*<<< orphan*/  descriptor_count ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ required_space (struct fw_descriptor*) ; 
 int /*<<< orphan*/  update_config_roms () ; 

void fw_core_remove_descriptor(struct fw_descriptor *desc)
{
	mutex_lock(&card_mutex);

	list_del(&desc->link);
	config_rom_length -= required_space(desc);
	descriptor_count--;
	if (desc->immediate > 0)
		descriptor_count--;
	update_config_roms();

	mutex_unlock(&card_mutex);
}