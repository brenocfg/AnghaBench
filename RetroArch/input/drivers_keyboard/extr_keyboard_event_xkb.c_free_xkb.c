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

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * mod_map_bit ; 
 int /*<<< orphan*/ * mod_map_idx ; 
 int /*<<< orphan*/  xkb_context_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xkb_ctx ; 
 int /*<<< orphan*/  xkb_keymap_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xkb_map ; 
 int /*<<< orphan*/ * xkb_state ; 
 int /*<<< orphan*/  xkb_state_unref (int /*<<< orphan*/ *) ; 

void free_xkb(void)
{
   if (mod_map_idx)
      free(mod_map_idx);
   if (mod_map_bit)
      free(mod_map_bit);
   if (xkb_map)
      xkb_keymap_unref(xkb_map);
   if (xkb_ctx)
      xkb_context_unref(xkb_ctx);
   if (xkb_state)
      xkb_state_unref(xkb_state);

   mod_map_idx = NULL;
   mod_map_bit = NULL;
   xkb_map     = NULL;
   xkb_ctx     = NULL;
   xkb_state   = NULL;
}