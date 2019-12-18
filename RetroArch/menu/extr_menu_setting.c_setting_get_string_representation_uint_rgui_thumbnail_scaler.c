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
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_RGUI_THUMB_SCALE_BILINEAR ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_RGUI_THUMB_SCALE_POINT ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_RGUI_THUMB_SCALE_SINC ; 
#define  RGUI_THUMB_SCALE_BILINEAR 130 
#define  RGUI_THUMB_SCALE_POINT 129 
#define  RGUI_THUMB_SCALE_SINC 128 
 int /*<<< orphan*/  msg_hash_to_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static void setting_get_string_representation_uint_rgui_thumbnail_scaler(
      rarch_setting_t *setting,
      char *s, size_t len)
{
   if (!setting)
      return;

   switch (*setting->value.target.unsigned_integer)
   {
      case RGUI_THUMB_SCALE_POINT:
         strlcpy(s,
               msg_hash_to_str(
                  MENU_ENUM_LABEL_VALUE_RGUI_THUMB_SCALE_POINT),
               len);
         break;
      case RGUI_THUMB_SCALE_BILINEAR:
         strlcpy(s,
               msg_hash_to_str(
                  MENU_ENUM_LABEL_VALUE_RGUI_THUMB_SCALE_BILINEAR),
               len);
         break;
      case RGUI_THUMB_SCALE_SINC:
         strlcpy(s,
               msg_hash_to_str(
                  MENU_ENUM_LABEL_VALUE_RGUI_THUMB_SCALE_SINC),
               len);
         break;
   }
}