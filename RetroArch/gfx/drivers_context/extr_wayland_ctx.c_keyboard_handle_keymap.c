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
typedef  scalar_t__ uint32_t ;
struct wl_keyboard {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RARCH_ERR (char*) ; 
 int /*<<< orphan*/  RARCH_LOG (char*) ; 
 scalar_t__ WL_KEYBOARD_KEYMAP_FORMAT_XKB_V1 ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ init_xkb (int,scalar_t__) ; 

__attribute__((used)) static void keyboard_handle_keymap(void* data,
      struct wl_keyboard* keyboard,
      uint32_t format,
      int fd,
      uint32_t size)
{
   (void)data;
   if (format != WL_KEYBOARD_KEYMAP_FORMAT_XKB_V1)
   {
      close(fd);
      return;
   }

#ifdef HAVE_XKBCOMMON
   if (init_xkb(fd, size) < 0)
      RARCH_ERR("[Wayland]: Failed to init keymap.\n");
#endif
   close(fd);

   RARCH_LOG("[Wayland]: Loaded keymap.\n");
}