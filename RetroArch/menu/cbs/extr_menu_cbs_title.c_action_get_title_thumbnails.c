#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  menu_driver; } ;
struct TYPE_5__ {TYPE_1__ arrays; } ;
typedef  TYPE_2__ settings_t ;
typedef  enum msg_hash_enums { ____Placeholder_msg_hash_enums } msg_hash_enums ;

/* Variables and functions */
 int MENU_ENUM_LABEL_VALUE_THUMBNAILS ; 
 int MENU_ENUM_LABEL_VALUE_THUMBNAILS_MATERIALUI ; 
 int MENU_ENUM_LABEL_VALUE_THUMBNAILS_RGUI ; 
 TYPE_2__* config_get_ptr () ; 
 char* msg_hash_to_str (int) ; 
 int /*<<< orphan*/  sanitize_to_string (char*,char const*,size_t) ; 
 int /*<<< orphan*/  string_is_empty (char const*) ; 
 scalar_t__ string_is_equal (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int action_get_title_thumbnails(
      const char *path, const char *label, unsigned menu_type, char *s, size_t len)
{
   settings_t *settings = config_get_ptr();
   const char *title    = NULL;
   enum msg_hash_enums label_value;

   /* Get label value */
   if (string_is_equal(settings->arrays.menu_driver, "rgui"))
      label_value = MENU_ENUM_LABEL_VALUE_THUMBNAILS_RGUI;
   else if (string_is_equal(settings->arrays.menu_driver, "glui"))
      label_value = MENU_ENUM_LABEL_VALUE_THUMBNAILS_MATERIALUI;
   else
      label_value = MENU_ENUM_LABEL_VALUE_THUMBNAILS;

   title = msg_hash_to_str(label_value);

   if (s && !string_is_empty(title))
   {
      sanitize_to_string(s, title, len);
      return 1;
   }

   return 0;
}