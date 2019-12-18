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
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_MENU_TICKER_TYPE_BOUNCE ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_MENU_TICKER_TYPE_LOOP ; 
#define  TICKER_TYPE_BOUNCE 129 
#define  TICKER_TYPE_LOOP 128 
 int /*<<< orphan*/  msg_hash_to_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static void setting_get_string_representation_uint_menu_ticker_type(
      rarch_setting_t *setting,
      char *s, size_t len)
{
   if (!setting)
      return;

   switch (*setting->value.target.unsigned_integer)
   {
      case TICKER_TYPE_BOUNCE:
         strlcpy(s,
               msg_hash_to_str(
                  MENU_ENUM_LABEL_VALUE_MENU_TICKER_TYPE_BOUNCE),
               len);
         break;
      case TICKER_TYPE_LOOP:
         strlcpy(s,
               msg_hash_to_str(
                  MENU_ENUM_LABEL_VALUE_MENU_TICKER_TYPE_LOOP),
               len);
         break;
   }
}