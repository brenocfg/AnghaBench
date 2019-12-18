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
#define  INPUT_TOGGLE_DOWN_SELECT 136 
#define  INPUT_TOGGLE_DOWN_Y_L_R 135 
#define  INPUT_TOGGLE_HOLD_START 134 
#define  INPUT_TOGGLE_L1_R1_START_SELECT 133 
#define  INPUT_TOGGLE_L3_R 132 
#define  INPUT_TOGGLE_L3_R3 131 
#define  INPUT_TOGGLE_L_R 130 
#define  INPUT_TOGGLE_NONE 129 
#define  INPUT_TOGGLE_START_SELECT 128 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_DOWN_SELECT ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_HOLD_START ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_NONE ; 
 char* msg_hash_to_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,size_t) ; 

__attribute__((used)) static void setting_get_string_representation_toggle_gamepad_combo(
      rarch_setting_t *setting,
      char *s, size_t len)
{
   if (!setting)
      return;

   switch (*setting->value.target.unsigned_integer)
   {
      case INPUT_TOGGLE_NONE:
         strlcpy(s, msg_hash_to_str(MENU_ENUM_LABEL_VALUE_NONE), len);
         break;
      case INPUT_TOGGLE_DOWN_Y_L_R:
         strlcpy(s, "Down + L1 + R1 + Y", len);
         break;
      case INPUT_TOGGLE_L3_R3:
         strlcpy(s, "L3 + R3", len);
         break;
      case INPUT_TOGGLE_L1_R1_START_SELECT:
         strlcpy(s, "L1 + R1 + Start + Select", len);
         break;
      case INPUT_TOGGLE_START_SELECT:
         strlcpy(s, "Start + Select", len);
         break;
      case INPUT_TOGGLE_L3_R:
         strlcpy(s, "L3 + R", len);
         break;
      case INPUT_TOGGLE_L_R:
         strlcpy(s, "L + R", len);
         break;
      case INPUT_TOGGLE_HOLD_START:
         strlcpy(s, msg_hash_to_str(MENU_ENUM_LABEL_VALUE_HOLD_START), len);
         break;
      case INPUT_TOGGLE_DOWN_SELECT:
         strlcpy(s, msg_hash_to_str(MENU_ENUM_LABEL_VALUE_DOWN_SELECT), len);
         break;
   }
}