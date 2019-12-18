#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned int loading_cheat_offset; unsigned int size; TYPE_1__* cheats; } ;
struct TYPE_3__ {unsigned int address; unsigned int address_mask; int big_endian; unsigned int cheat_type; int state; unsigned int handler; unsigned int memory_search_size; unsigned int repeat_add_to_address; unsigned int repeat_add_to_value; unsigned int repeat_count; unsigned int rumble_port; unsigned int rumble_primary_duration; unsigned int rumble_primary_strength; unsigned int rumble_secondary_duration; unsigned int rumble_secondary_strength; unsigned int rumble_type; unsigned int rumble_value; unsigned int value; void* desc; void* code; } ;

/* Variables and functions */
 TYPE_2__ cheat_manager_state ; 
 scalar_t__ errno ; 
 void* strdup (char*) ; 
 scalar_t__ string_is_equal (char*,char*) ; 
 size_t strlen (char const*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 scalar_t__ strtoul (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cheat_manager_load_cb_second_pass(char *key, char *value)
{
   char cheat_num_str[20];
   unsigned cheat_num;
   unsigned cheat_idx;
   unsigned idx = 5;
   size_t key_length = 0;
   errno = 0;

   if (strncmp(key, "cheat", 5) != 0)
      return;

   key_length = strlen((const char*)key);

   while (idx < key_length && key[idx] >= '0' && key[idx] <= '9' && idx < 24)
   {
      cheat_num_str[idx - 5] = key[idx];
      idx++;
   }

   cheat_num_str[idx - 5] = '\0';

   cheat_num = (unsigned)strtoul(cheat_num_str, NULL, 0);

   if (cheat_num + cheat_manager_state.loading_cheat_offset >= cheat_manager_state.size)
      return;

   key = key + idx + 1;

   cheat_idx = cheat_num + cheat_manager_state.loading_cheat_offset;

   if (string_is_equal(key, "address"))
      cheat_manager_state.cheats[cheat_idx].address = (unsigned)strtoul(value, NULL, 0);
   else if (string_is_equal(key, "address_bit_position"))
      cheat_manager_state.cheats[cheat_idx].address_mask = (unsigned)strtoul(value, NULL, 0);
   else if (string_is_equal(key, "big_endian"))
      cheat_manager_state.cheats[cheat_idx].big_endian = (string_is_equal(value, "true") || string_is_equal(value, "1"));
   else if (string_is_equal(key, "cheat_type"))
      cheat_manager_state.cheats[cheat_idx].cheat_type = (unsigned)strtoul(value, NULL, 0);
   else if (string_is_equal(key, "code"))
      cheat_manager_state.cheats[cheat_idx].code = strdup(value);
   else if (string_is_equal(key, "desc"))
      cheat_manager_state.cheats[cheat_idx].desc = strdup(value);
   else if (string_is_equal(key, "enable"))
      cheat_manager_state.cheats[cheat_idx].state = (string_is_equal(value, "true") || string_is_equal(value, "1"));
   else if (string_is_equal(key, "handler"))
      cheat_manager_state.cheats[cheat_idx].handler = (unsigned)strtoul(value, NULL, 0);
   else if (string_is_equal(key, "memory_search_size"))
      cheat_manager_state.cheats[cheat_idx].memory_search_size = (unsigned)strtoul(value, NULL, 0);
   else if (string_is_equal(key, "repeat_add_to_address"))
      cheat_manager_state.cheats[cheat_idx].repeat_add_to_address = (unsigned)strtoul(value, NULL, 0);
   else if (string_is_equal(key, "repeat_add_to_value"))
      cheat_manager_state.cheats[cheat_idx].repeat_add_to_value = (unsigned)strtoul(value, NULL, 0);
   else if (string_is_equal(key, "repeat_count"))
      cheat_manager_state.cheats[cheat_idx].repeat_count = (unsigned)strtoul(value, NULL, 0);
   else if (string_is_equal(key, "rumble_port"))
      cheat_manager_state.cheats[cheat_idx].rumble_port = (unsigned)strtoul(value, NULL, 0);
   else if (string_is_equal(key, "rumble_primary_duration"))
      cheat_manager_state.cheats[cheat_idx].rumble_primary_duration = (unsigned)strtoul(value, NULL, 0);
   else if (string_is_equal(key, "rumble_primary_strength"))
      cheat_manager_state.cheats[cheat_idx].rumble_primary_strength = (unsigned)strtoul(value, NULL, 0);
   else if (string_is_equal(key, "rumble_secondary_duration"))
      cheat_manager_state.cheats[cheat_idx].rumble_secondary_duration = (unsigned)strtoul(value, NULL, 0);
   else if (string_is_equal(key, "rumble_secondary_strength"))
      cheat_manager_state.cheats[cheat_idx].rumble_secondary_strength = (unsigned)strtoul(value, NULL, 0);
   else if (string_is_equal(key, "rumble_type"))
      cheat_manager_state.cheats[cheat_idx].rumble_type = (unsigned)strtoul(value, NULL, 0);
   else if (string_is_equal(key, "rumble_value"))
      cheat_manager_state.cheats[cheat_idx].rumble_value = (unsigned)strtoul(value, NULL, 0);
   else if (string_is_equal(key, "value"))
      cheat_manager_state.cheats[cheat_idx].value = (unsigned)strtoul(value, NULL, 0);
}