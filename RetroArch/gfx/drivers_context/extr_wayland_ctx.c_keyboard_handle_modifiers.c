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
typedef  int /*<<< orphan*/  uint32_t ;
struct wl_keyboard {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  handle_xkb_state_mask (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void keyboard_handle_modifiers(void *data,
      struct wl_keyboard *keyboard,
      uint32_t serial,
      uint32_t modsDepressed,
      uint32_t modsLatched,
      uint32_t modsLocked,
      uint32_t group)
{
   (void)data;
   (void)keyboard;
   (void)serial;
#ifdef HAVE_XKBCOMMON
   handle_xkb_state_mask(modsDepressed, modsLatched, modsLocked, group);
#else
   (void)modsDepressed;
   (void)modsLatched;
   (void)modsLocked;
   (void)group;
#endif
}