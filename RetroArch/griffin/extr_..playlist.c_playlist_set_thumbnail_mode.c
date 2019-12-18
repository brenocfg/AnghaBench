#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int right_thumbnail_mode; int modified; int left_thumbnail_mode; } ;
typedef  TYPE_1__ playlist_t ;
typedef  enum playlist_thumbnail_mode { ____Placeholder_playlist_thumbnail_mode } playlist_thumbnail_mode ;
typedef  enum playlist_thumbnail_id { ____Placeholder_playlist_thumbnail_id } playlist_thumbnail_id ;

/* Variables and functions */
 int PLAYLIST_THUMBNAIL_LEFT ; 
 int PLAYLIST_THUMBNAIL_RIGHT ; 

void playlist_set_thumbnail_mode(
      playlist_t *playlist, enum playlist_thumbnail_id thumbnail_id, enum playlist_thumbnail_mode thumbnail_mode)
{
   if (!playlist)
      return;

   if (thumbnail_id == PLAYLIST_THUMBNAIL_RIGHT)
   {
      playlist->right_thumbnail_mode = thumbnail_mode;
      playlist->modified = true;
   }
   else if (thumbnail_id == PLAYLIST_THUMBNAIL_LEFT)
   {
      playlist->left_thumbnail_mode = thumbnail_mode;
      playlist->modified = true;
   }
}