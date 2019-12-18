#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {char* savestate_thumbnail_file_path; } ;
typedef  TYPE_4__ stripes_handle_t ;
struct TYPE_13__ {int state_slot; } ;
struct TYPE_12__ {scalar_t__ savestate_thumbnail_enable; } ;
struct TYPE_16__ {TYPE_2__ ints; TYPE_1__ bools; } ;
typedef  TYPE_5__ settings_t ;
struct TYPE_17__ {char* label; } ;
typedef  TYPE_6__ menu_entry_t ;
struct TYPE_14__ {char* savestate; } ;
struct TYPE_18__ {TYPE_3__ name; } ;
typedef  TYPE_7__ global_t ;

/* Variables and functions */
 TYPE_5__* config_get_ptr () ; 
 int /*<<< orphan*/  fill_pathname_join_delim (char*,char*,char*,char,size_t) ; 
 int /*<<< orphan*/  free (char*) ; 
 TYPE_7__* global_get_ptr () ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  menu_entry_get (TYPE_6__*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  menu_entry_init (TYPE_6__*) ; 
 scalar_t__ path_is_valid (char*) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,char*,int) ; 
 char* strdup (char*) ; 
 int /*<<< orphan*/  string_is_empty (char*) ; 
 scalar_t__ string_is_equal (char*,char*) ; 
 int /*<<< orphan*/  strlcat (char*,char*,size_t) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,size_t) ; 

__attribute__((used)) static void stripes_update_savestate_thumbnail_path(void *data, unsigned i)
{
   menu_entry_t entry;
   settings_t     *settings = config_get_ptr();
   stripes_handle_t     *stripes    = (stripes_handle_t*)data;

   if (!stripes)
      return;

   menu_entry_init(&entry);
   menu_entry_get(&entry, 0, i, NULL, true);

   if (!string_is_empty(stripes->savestate_thumbnail_file_path))
      free(stripes->savestate_thumbnail_file_path);
   stripes->savestate_thumbnail_file_path = NULL;

   if (!string_is_empty(entry.label))
   {
      if (     (settings->bools.savestate_thumbnail_enable)
            && ((string_is_equal(entry.label, "state_slot"))
               || (string_is_equal(entry.label, "loadstate"))
               || (string_is_equal(entry.label, "savestate"))))
      {
         size_t path_size         = 8024 * sizeof(char);
         char             *path   = (char*)malloc(8204 * sizeof(char));
         global_t         *global = global_get_ptr();

         path[0] = '\0';

         if (global)
         {
            int state_slot = settings->ints.state_slot;

            if (state_slot > 0)
               snprintf(path, path_size, "%s%d",
                     global->name.savestate, state_slot);
            else if (state_slot < 0)
               fill_pathname_join_delim(path,
                     global->name.savestate, "auto", '.', path_size);
            else
               strlcpy(path, global->name.savestate, path_size);
         }

         strlcat(path, ".png", path_size);

         if (path_is_valid(path))
         {
            if (!string_is_empty(stripes->savestate_thumbnail_file_path))
               free(stripes->savestate_thumbnail_file_path);
            stripes->savestate_thumbnail_file_path = strdup(path);
         }

         free(path);
      }
   }
}