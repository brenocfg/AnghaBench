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
struct tps_key_entry {int code; } ;

/* Variables and functions */
 struct tps_key_entry* topstar_keymap ; 

__attribute__((used)) static struct tps_key_entry *tps_get_key_by_scancode(int code)
{
	struct tps_key_entry *key;

	for (key = topstar_keymap; key->code; key++)
		if (code == key->code)
			return key;

	return NULL;
}