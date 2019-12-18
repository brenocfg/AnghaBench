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
struct key_entry {scalar_t__ type; int code; } ;

/* Variables and functions */
 scalar_t__ KE_END ; 
 struct key_entry* hp_wmi_keymap ; 

__attribute__((used)) static struct key_entry *hp_wmi_get_entry_by_scancode(int code)
{
	struct key_entry *key;

	for (key = hp_wmi_keymap; key->type != KE_END; key++)
		if (code == key->code)
			return key;

	return NULL;
}