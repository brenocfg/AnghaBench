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
struct TYPE_5__ {size_t* unsigned_integer; } ;
struct TYPE_6__ {TYPE_1__ target; } ;
struct TYPE_7__ {TYPE_2__ value; } ;
typedef  TYPE_3__ rarch_setting_t ;

/* Variables and functions */
 size_t ANALOG_DPAD_LAST ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_LEFT_ANALOG ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_NONE ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_RIGHT_ANALOG ; 
 char* msg_hash_to_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,size_t) ; 

__attribute__((used)) static void setting_get_string_representation_uint_analog_dpad_mode(
      rarch_setting_t *setting,
      char *s, size_t len)
{
   const char *modes[3];

   modes[0] = msg_hash_to_str(MENU_ENUM_LABEL_VALUE_NONE);
   modes[1] = msg_hash_to_str(MENU_ENUM_LABEL_VALUE_LEFT_ANALOG);
   modes[2] = msg_hash_to_str(MENU_ENUM_LABEL_VALUE_RIGHT_ANALOG);

   strlcpy(s, modes[*setting->value.target.unsigned_integer % ANALOG_DPAD_LAST], len);
}