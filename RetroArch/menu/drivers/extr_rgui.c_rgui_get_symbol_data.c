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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  enum rgui_symbol_type { ____Placeholder_rgui_symbol_type } rgui_symbol_type ;

/* Variables and functions */
#define  RGUI_SYMBOL_BACKSPACE 140 
#define  RGUI_SYMBOL_BATTERY_100 139 
#define  RGUI_SYMBOL_BATTERY_20 138 
#define  RGUI_SYMBOL_BATTERY_40 137 
#define  RGUI_SYMBOL_BATTERY_60 136 
#define  RGUI_SYMBOL_BATTERY_80 135 
#define  RGUI_SYMBOL_CHARGING 134 
#define  RGUI_SYMBOL_CHECKMARK 133 
#define  RGUI_SYMBOL_ENTER 132 
#define  RGUI_SYMBOL_NEXT 131 
#define  RGUI_SYMBOL_SHIFT_DOWN 130 
#define  RGUI_SYMBOL_SHIFT_UP 129 
#define  RGUI_SYMBOL_TEXT_CURSOR 128 
 int /*<<< orphan*/  const* rgui_symbol_data_backspace ; 
 int /*<<< orphan*/  const* rgui_symbol_data_battery_100 ; 
 int /*<<< orphan*/  const* rgui_symbol_data_battery_20 ; 
 int /*<<< orphan*/  const* rgui_symbol_data_battery_40 ; 
 int /*<<< orphan*/  const* rgui_symbol_data_battery_60 ; 
 int /*<<< orphan*/  const* rgui_symbol_data_battery_80 ; 
 int /*<<< orphan*/  const* rgui_symbol_data_charging ; 
 int /*<<< orphan*/  const* rgui_symbol_data_checkmark ; 
 int /*<<< orphan*/  const* rgui_symbol_data_enter ; 
 int /*<<< orphan*/  const* rgui_symbol_data_next ; 
 int /*<<< orphan*/  const* rgui_symbol_data_shift_down ; 
 int /*<<< orphan*/  const* rgui_symbol_data_shift_up ; 
 int /*<<< orphan*/  const* rgui_symbol_data_text_cursor ; 

__attribute__((used)) static const uint8_t *rgui_get_symbol_data(enum rgui_symbol_type symbol)
{
   switch (symbol)
   {
      case RGUI_SYMBOL_BACKSPACE:
         return rgui_symbol_data_backspace;
      case RGUI_SYMBOL_ENTER:
         return rgui_symbol_data_enter;
      case RGUI_SYMBOL_SHIFT_UP:
         return rgui_symbol_data_shift_up;
      case RGUI_SYMBOL_SHIFT_DOWN:
         return rgui_symbol_data_shift_down;
      case RGUI_SYMBOL_NEXT:
         return rgui_symbol_data_next;
      case RGUI_SYMBOL_TEXT_CURSOR:
         return rgui_symbol_data_text_cursor;
      case RGUI_SYMBOL_CHARGING:
         return rgui_symbol_data_charging;
      case RGUI_SYMBOL_BATTERY_100:
         return rgui_symbol_data_battery_100;
      case RGUI_SYMBOL_BATTERY_80:
         return rgui_symbol_data_battery_80;
      case RGUI_SYMBOL_BATTERY_60:
         return rgui_symbol_data_battery_60;
      case RGUI_SYMBOL_BATTERY_40:
         return rgui_symbol_data_battery_40;
      case RGUI_SYMBOL_BATTERY_20:
         return rgui_symbol_data_battery_20;
      case RGUI_SYMBOL_CHECKMARK:
         return rgui_symbol_data_checkmark;
      default:
         break;
   }

   return NULL;
}