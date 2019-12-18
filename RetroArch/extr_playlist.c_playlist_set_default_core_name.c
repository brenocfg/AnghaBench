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
struct TYPE_3__ {int modified; scalar_t__ default_core_name; } ;
typedef  TYPE_1__ playlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (scalar_t__) ; 
 scalar_t__ strdup (char const*) ; 
 scalar_t__ string_is_empty (char const*) ; 
 int /*<<< orphan*/  string_is_equal (scalar_t__,char const*) ; 

void playlist_set_default_core_name(playlist_t *playlist, const char *core_name)
{
   if (!playlist || string_is_empty(core_name))
      return;

   if (!string_is_equal(playlist->default_core_name, core_name))
   {
      if (playlist->default_core_name)
         free(playlist->default_core_name);
      playlist->default_core_name = strdup(core_name);
      playlist->modified = true;
   }
}