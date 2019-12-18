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
struct string_list {scalar_t__ size; } ;
struct retro_subsystem_info {scalar_t__ num_roms; char* desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_ERROR_LIBRETRO_CORE_REQUIRES_SPECIAL_CONTENT ; 
 int /*<<< orphan*/  RARCH_PATH_SUBSYSTEM ; 
 int /*<<< orphan*/  free (char*) ; 
 struct retro_subsystem_info* libretro_find_subsystem_info (struct retro_subsystem_info const*,unsigned int,char*) ; 
 scalar_t__ malloc (size_t) ; 
 int /*<<< orphan*/  msg_hash_to_str (int /*<<< orphan*/ ) ; 
 char* path_get (int /*<<< orphan*/ ) ; 
 struct string_list* path_get_subsystem_list () ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,char*,...) ; 
 char* strdup (char*) ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static const struct
retro_subsystem_info *content_file_init_subsystem(
      const struct retro_subsystem_info *subsystem_data,
      size_t subsystem_current_count,
      char **error_string,
      bool *ret)
{
   size_t path_size                           = 1024 * sizeof(char);
   char *msg                                  = (char*)malloc(path_size);
   struct string_list *subsystem              = path_get_subsystem_list();
   const struct retro_subsystem_info *special = libretro_find_subsystem_info(
            subsystem_data, (unsigned)subsystem_current_count,
            path_get(RARCH_PATH_SUBSYSTEM));

   msg[0] = '\0';

   if (!special)
   {
      snprintf(msg, path_size,
            "Failed to find subsystem \"%s\" in libretro implementation.\n",
            path_get(RARCH_PATH_SUBSYSTEM));
      *error_string = strdup(msg);
      goto error;
   }

   if (special->num_roms && !subsystem)
   {
      strlcpy(msg,
            msg_hash_to_str(MSG_ERROR_LIBRETRO_CORE_REQUIRES_SPECIAL_CONTENT),
            path_size
            );
      *error_string = strdup(msg);
      goto error;
   }
   else if (special->num_roms && (special->num_roms != subsystem->size))
   {
      snprintf(msg,
            path_size,
            "Libretro core requires %u content files for "
            "subsystem \"%s\", but %u content files were provided.\n",
            special->num_roms, special->desc,
            (unsigned)subsystem->size);
      *error_string = strdup(msg);
      goto error;
   }
   else if (!special->num_roms && subsystem && subsystem->size)
   {
      snprintf(msg,
            path_size,
            "Libretro core takes no content for subsystem \"%s\", "
            "but %u content files were provided.\n",
            special->desc,
            (unsigned)subsystem->size);
      *error_string = strdup(msg);
      goto error;
   }

   *ret = true;
   free(msg);
   return special;

error:
   *ret = false;
   free(msg);
   return NULL;
}