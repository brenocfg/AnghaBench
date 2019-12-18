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
 int /*<<< orphan*/  retro_assert (int) ; 
 int /*<<< orphan*/  uwp_open_broadfilesystemaccess_settings () ; 

__attribute__((used)) static int action_ok_open_uwp_permission_settings(const char *path,
   const char *label, unsigned type, size_t idx, size_t entry_idx)
{
#ifdef __WINRT__
   uwp_open_broadfilesystemaccess_settings();
#else
   retro_assert(false);
#endif
   return 0;
}