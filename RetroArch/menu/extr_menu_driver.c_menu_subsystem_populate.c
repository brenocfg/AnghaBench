#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tmp ;
struct retro_subsystem_info {int num_roms; char* desc; TYPE_3__* roms; } ;
typedef  int /*<<< orphan*/  star_char ;
struct TYPE_9__ {int /*<<< orphan*/  menu_show_sublabels; } ;
struct TYPE_8__ {int /*<<< orphan*/  menu_driver; } ;
struct TYPE_11__ {TYPE_2__ bools; TYPE_1__ arrays; } ;
typedef  TYPE_4__ settings_t ;
typedef  int /*<<< orphan*/  s ;
typedef  int /*<<< orphan*/  rom_buff ;
struct TYPE_12__ {int /*<<< orphan*/  list; } ;
typedef  TYPE_5__ menu_displaylist_info_t ;
struct TYPE_10__ {char* desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  MENU_ENUM_LABEL_SUBSYSTEM_ADD ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_SUBSYSTEM_LOAD ; 
 scalar_t__ MENU_SETTINGS_SUBSYSTEM_ADD ; 
 scalar_t__ MENU_SETTINGS_SUBSYSTEM_LOAD ; 
 int PATH_MAX_LENGTH ; 
 int /*<<< orphan*/  RARCH_WARN (char*) ; 
 TYPE_4__* config_get_ptr () ; 
 unsigned int content_get_subsystem () ; 
 int /*<<< orphan*/  content_get_subsystem_rom (unsigned int) ; 
 int content_get_subsystem_rom_id () ; 
 int /*<<< orphan*/  menu_entries_append_enum (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_hash_to_str (int /*<<< orphan*/ ) ; 
 char* path_basename (int /*<<< orphan*/ ) ; 
 int snprintf (char*,int,char*,char*,...) ; 
 int /*<<< orphan*/  string_is_empty (char*) ; 
 int string_is_equal (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strlcat (char*,char*,int) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 
 unsigned int subsystem_current_count ; 
 scalar_t__ verbosity_is_enabled () ; 

void menu_subsystem_populate(const struct retro_subsystem_info* subsystem, menu_displaylist_info_t *info)
{
   settings_t *settings = config_get_ptr();
   /* Note: Create this string here explicitly (rather than
    * using a #define elsewhere) since we need to be aware of
    * its length... */
#if defined(__APPLE__)
   /* UTF-8 support is currently broken on Apple devices... */
   static const char utf8_star_char[] = "*";
#else
   /* <BLACK STAR>
    * UCN equivalent: "\u2605" */
   static const char utf8_star_char[] = "\xE2\x98\x85";
#endif
   char star_char[16];
   unsigned i = 0;
   int n = 0;
   bool is_rgui = string_is_equal(settings->arrays.menu_driver, "rgui");
   
   /* Select appropriate 'star' marker for subsystem menu entries
    * (i.e. RGUI does not support unicode, so use a 'standard'
    * character fallback) */
   snprintf(star_char, sizeof(star_char), "%s", is_rgui ? "*" : utf8_star_char);
   
   if (subsystem && subsystem_current_count > 0)
   {
      for (i = 0; i < subsystem_current_count; i++, subsystem++)
      {
         char s[PATH_MAX_LENGTH];
         if (content_get_subsystem() == i)
         {
            if (content_get_subsystem_rom_id() < subsystem->num_roms)
            {
               snprintf(s, sizeof(s),
                  "Load %s %s",
                  subsystem->desc,
                  star_char);
               
               /* If using RGUI with sublabels disabled, add the
                * appropriate text to the menu entry itself... */
               if (is_rgui && !settings->bools.menu_show_sublabels)
               {
                  char tmp[PATH_MAX_LENGTH];
                  
                  n = snprintf(tmp, sizeof(tmp),
                     "%s [%s %s]", s, "Current Content:",
                     subsystem->roms[content_get_subsystem_rom_id()].desc);

                  /* Stupid GCC will warn about snprintf() truncation even though
                   * we couldn't care less about it (if the menu entry label gets
                   * truncated then the string will already be too long to view in
                   * any usable manner on screen, so the fact that the end is
                   * missing is irrelevant). There are two ways to silence this noise:
                   * 1) Make the destination buffers large enough that text cannot be
                   *    truncated. This is a waste of memory.
                   * 2) Check the snprintf() return value (and take action). This is
                   *    the most harmless option, so we just print a warning if anything
                   *    is truncated.
                   * To reiterate: The actual warning generated here is pointless, and
                   * should be ignored. */
                  if ((n < 0) || (n >= PATH_MAX_LENGTH))
                  {
                     if (verbosity_is_enabled())
                     {
                        RARCH_WARN("Menu subsystem entry: Description label truncated.\n");
                     }
                  }

                  strlcpy(s, tmp, sizeof(s));
               }
               
               menu_entries_append_enum(info->list,
                  s,
                  msg_hash_to_str(MENU_ENUM_LABEL_SUBSYSTEM_ADD),
                  MENU_ENUM_LABEL_SUBSYSTEM_ADD,
                  MENU_SETTINGS_SUBSYSTEM_ADD + i, 0, 0);
            }
            else
            {
               snprintf(s, sizeof(s),
                  "Start %s %s",
                  subsystem->desc,
                  star_char);
               
               /* If using RGUI with sublabels disabled, add the
                * appropriate text to the menu entry itself... */
               if (is_rgui && !settings->bools.menu_show_sublabels)
               {
                  unsigned j = 0;
                  char rom_buff[PATH_MAX_LENGTH];
                  char tmp[PATH_MAX_LENGTH];
                  rom_buff[0] = '\0';

                  for (j = 0; j < content_get_subsystem_rom_id(); j++)
                  {
                     strlcat(rom_buff,
                           path_basename(content_get_subsystem_rom(j)), sizeof(rom_buff));
                     if (j != content_get_subsystem_rom_id() - 1)
                        strlcat(rom_buff, "|", sizeof(rom_buff));
                  }

                  if (!string_is_empty(rom_buff))
                  {
                     n = snprintf(tmp, sizeof(tmp), "%s [%s]", s, rom_buff);
                     
                     /* More snprintf() gcc warning suppression... */
                     if ((n < 0) || (n >= PATH_MAX_LENGTH))
                     {
                        if (verbosity_is_enabled())
                        {
                           RARCH_WARN("Menu subsystem entry: Description label truncated.\n");
                        }
                     }
                     
                     strlcpy(s, tmp, sizeof(s));
                  }
               }
               
               menu_entries_append_enum(info->list,
                  s,
                  msg_hash_to_str(MENU_ENUM_LABEL_SUBSYSTEM_LOAD),
                  MENU_ENUM_LABEL_SUBSYSTEM_LOAD,
                  MENU_SETTINGS_SUBSYSTEM_LOAD, 0, 0);
            }
         }
         else
         {
            snprintf(s, sizeof(s),
               "Load %s",
               subsystem->desc);
            
            /* If using RGUI with sublabels disabled, add the
             * appropriate text to the menu entry itself... */
            if (is_rgui && !settings->bools.menu_show_sublabels)
            {
               /* This check is probably not required (it's not done
                * in menu_cbs_sublabel.c action_bind_sublabel_subsystem_add(),
                * anyway), but no harm in being safe... */
               if (subsystem->num_roms > 0)
               {
                  char tmp[PATH_MAX_LENGTH];
                  
                  n = snprintf(tmp, sizeof(tmp),
                     "%s [%s %s]", s, "Current Content:",
                     subsystem->roms[0].desc);
                  
                  /* More snprintf() gcc warning suppression... */
                  if ((n < 0) || (n >= PATH_MAX_LENGTH))
                  {
                     if (verbosity_is_enabled())
                     {
                        RARCH_WARN("Menu subsystem entry: Description label truncated.\n");
                     }
                  }
                  
                  strlcpy(s, tmp, sizeof(s));
               }
            }
            
            menu_entries_append_enum(info->list,
               s,
               msg_hash_to_str(MENU_ENUM_LABEL_SUBSYSTEM_ADD),
               MENU_ENUM_LABEL_SUBSYSTEM_ADD,
               MENU_SETTINGS_SUBSYSTEM_ADD + i, 0, 0);
         }
      }
   }
}