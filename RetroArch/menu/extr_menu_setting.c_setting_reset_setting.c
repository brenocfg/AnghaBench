#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  string; int /*<<< orphan*/ * keybind; int /*<<< orphan*/  fraction; int /*<<< orphan*/  sizet; int /*<<< orphan*/  unsigned_integer; int /*<<< orphan*/  integer; int /*<<< orphan*/  boolean; } ;
struct TYPE_9__ {int /*<<< orphan*/  string; int /*<<< orphan*/ * keybind; int /*<<< orphan*/ * fraction; int /*<<< orphan*/ * sizet; int /*<<< orphan*/ * unsigned_integer; int /*<<< orphan*/ * integer; int /*<<< orphan*/ * boolean; } ;
struct TYPE_10__ {TYPE_1__ target; } ;
struct TYPE_12__ {int /*<<< orphan*/  (* change_handler ) (TYPE_4__*) ;int /*<<< orphan*/  size; TYPE_3__ default_value; TYPE_2__ value; } ;
typedef  TYPE_4__ rarch_setting_t ;

/* Variables and functions */
#define  ST_BIND 137 
#define  ST_BOOL 136 
#define  ST_DIR 135 
#define  ST_FLOAT 134 
#define  ST_INT 133 
#define  ST_PATH 132 
#define  ST_SIZE 131 
#define  ST_STRING 130 
#define  ST_STRING_OPTIONS 129 
#define  ST_UINT 128 
 int /*<<< orphan*/  fill_pathname_expand_special (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int const setting_get_type (TYPE_4__*) ; 
 int /*<<< orphan*/  setting_set_with_string_representation (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*) ; 

__attribute__((used)) static void setting_reset_setting(rarch_setting_t* setting)
{
   if (!setting)
      return;

   switch (setting_get_type(setting))
   {
      case ST_BOOL:
         *setting->value.target.boolean          = setting->default_value.boolean;
         break;
      case ST_INT:
         *setting->value.target.integer          = setting->default_value.integer;
         break;
      case ST_UINT:
         *setting->value.target.unsigned_integer = setting->default_value.unsigned_integer;
         break;
      case ST_SIZE:
         *setting->value.target.sizet            = setting->default_value.sizet;
         break;
      case ST_FLOAT:
         *setting->value.target.fraction         = setting->default_value.fraction;
         break;
      case ST_BIND:
         *setting->value.target.keybind          = *setting->default_value.keybind;
         break;
      case ST_STRING:
      case ST_STRING_OPTIONS:
      case ST_PATH:
      case ST_DIR:
         if (setting->default_value.string)
         {
            if (setting_get_type(setting) == ST_STRING)
               setting_set_with_string_representation(setting, setting->default_value.string);
            else
               fill_pathname_expand_special(setting->value.target.string,
                     setting->default_value.string, setting->size);
         }
         break;
      default:
         break;
   }

   if (setting->change_handler)
      setting->change_handler(setting);
}