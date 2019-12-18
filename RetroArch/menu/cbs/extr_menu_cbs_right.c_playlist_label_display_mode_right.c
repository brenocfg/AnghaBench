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
typedef  int /*<<< orphan*/  playlist_t ;
typedef  enum playlist_label_display_mode { ____Placeholder_playlist_label_display_mode } playlist_label_display_mode ;

/* Variables and functions */
 int LABEL_DISPLAY_MODE_DEFAULT ; 
 int LABEL_DISPLAY_MODE_KEEP_REGION_AND_DISC_INDEX ; 
 int /*<<< orphan*/ * playlist_get_cached () ; 
 int playlist_get_label_display_mode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  playlist_set_label_display_mode (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  playlist_write_file (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int playlist_label_display_mode_right(unsigned type, const char *label,
      bool wraparound)
{
   enum playlist_label_display_mode label_display_mode;
   playlist_t *playlist             = playlist_get_cached();

   if (!playlist)
      return -1;

   label_display_mode = playlist_get_label_display_mode(playlist);

   if (label_display_mode != LABEL_DISPLAY_MODE_KEEP_REGION_AND_DISC_INDEX)
      label_display_mode = (enum playlist_label_display_mode)((int)label_display_mode + 1);
   else if (wraparound)
      label_display_mode = LABEL_DISPLAY_MODE_DEFAULT;

   playlist_set_label_display_mode(playlist, label_display_mode);
   playlist_write_file(playlist);

   return 0;
}