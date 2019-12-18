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
 int /*<<< orphan*/  FILEBROWSER_SELECT_IMAGE ; 
 int action_ok_lookup_setting (char const*,char const*,unsigned int,size_t,size_t) ; 
 int /*<<< orphan*/  filebrowser_set_type (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int action_ok_menu_wallpaper(const char *path,
      const char *label, unsigned type, size_t idx, size_t entry_idx)
{
   filebrowser_set_type(FILEBROWSER_SELECT_IMAGE);
   return action_ok_lookup_setting(path, label, type, idx, entry_idx);
}