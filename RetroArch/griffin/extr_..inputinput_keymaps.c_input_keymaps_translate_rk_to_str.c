#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  enum retro_key { ____Placeholder_retro_key } retro_key ;
struct TYPE_2__ {int key; scalar_t__ str; } ;

/* Variables and functions */
 int RETROK_a ; 
 int RETROK_z ; 
 TYPE_1__* input_config_key_map ; 
 int /*<<< orphan*/  retro_assert (int) ; 
 int /*<<< orphan*/  strlcpy (char*,scalar_t__,size_t) ; 

void input_keymaps_translate_rk_to_str(enum retro_key key, char *buf, size_t size)
{
   unsigned i;

   retro_assert(size >= 2);
   *buf = '\0';

   if (key >= RETROK_a && key <= RETROK_z)
   {
      buf[0] = (key - RETROK_a) + 'a';
      buf[1] = '\0';
      return;
   }

   for (i = 0; input_config_key_map[i].str; i++)
   {
      if (input_config_key_map[i].key != key)
         continue;

      strlcpy(buf, input_config_key_map[i].str, size);
      break;
   }
}