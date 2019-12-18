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
 unsigned int UDEV_MAX_KEYS ; 
 int /*<<< orphan*/  free_xkb () ; 
 scalar_t__* udev_key_state ; 

__attribute__((used)) static void udev_input_kb_free(void)
{
   unsigned i;

   for (i = 0; i < UDEV_MAX_KEYS; i++)
      udev_key_state[i] = 0;

#ifdef UDEV_XKB_HANDLING
   free_xkb();
#endif
}