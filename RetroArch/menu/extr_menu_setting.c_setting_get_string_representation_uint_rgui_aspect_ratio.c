#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int* unsigned_integer; } ;
struct TYPE_6__ {TYPE_1__ target; } ;
struct TYPE_7__ {TYPE_2__ value; } ;
typedef  TYPE_3__ rarch_setting_t ;

/* Variables and functions */
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_RGUI_ASPECT_RATIO_16_10 ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_RGUI_ASPECT_RATIO_16_10_CENTRE ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_RGUI_ASPECT_RATIO_16_9 ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_RGUI_ASPECT_RATIO_16_9_CENTRE ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_RGUI_ASPECT_RATIO_4_3 ; 
#define  RGUI_ASPECT_RATIO_16_10 132 
#define  RGUI_ASPECT_RATIO_16_10_CENTRE 131 
#define  RGUI_ASPECT_RATIO_16_9 130 
#define  RGUI_ASPECT_RATIO_16_9_CENTRE 129 
#define  RGUI_ASPECT_RATIO_4_3 128 
 int /*<<< orphan*/  msg_hash_to_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static void setting_get_string_representation_uint_rgui_aspect_ratio(
      rarch_setting_t *setting,
      char *s, size_t len)
{
   if (!setting)
      return;

   switch (*setting->value.target.unsigned_integer)
   {
      case RGUI_ASPECT_RATIO_4_3:
         strlcpy(s,
               msg_hash_to_str(
                  MENU_ENUM_LABEL_VALUE_RGUI_ASPECT_RATIO_4_3),
               len);
         break;
      case RGUI_ASPECT_RATIO_16_9:
         strlcpy(s,
               msg_hash_to_str(
                  MENU_ENUM_LABEL_VALUE_RGUI_ASPECT_RATIO_16_9),
               len);
         break;
      case RGUI_ASPECT_RATIO_16_9_CENTRE:
         strlcpy(s,
               msg_hash_to_str(
                  MENU_ENUM_LABEL_VALUE_RGUI_ASPECT_RATIO_16_9_CENTRE),
               len);
         break;
      case RGUI_ASPECT_RATIO_16_10:
         strlcpy(s,
               msg_hash_to_str(
                  MENU_ENUM_LABEL_VALUE_RGUI_ASPECT_RATIO_16_10),
               len);
         break;
      case RGUI_ASPECT_RATIO_16_10_CENTRE:
         strlcpy(s,
               msg_hash_to_str(
                  MENU_ENUM_LABEL_VALUE_RGUI_ASPECT_RATIO_16_10_CENTRE),
               len);
         break;
   }
}