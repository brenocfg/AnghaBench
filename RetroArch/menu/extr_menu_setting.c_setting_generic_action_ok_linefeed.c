#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  name; int /*<<< orphan*/  short_description; } ;
typedef  TYPE_1__ rarch_setting_t ;
struct TYPE_7__ {int /*<<< orphan*/ * cb; scalar_t__ idx; scalar_t__ type; int /*<<< orphan*/  label_setting; int /*<<< orphan*/  label; } ;
typedef  TYPE_2__ menu_input_ctx_line_t ;
typedef  int /*<<< orphan*/ * input_keyboard_line_complete_t ;

/* Variables and functions */
#define  ST_HEX 132 
#define  ST_SIZE 131 
#define  ST_STRING 130 
#define  ST_STRING_OPTIONS 129 
#define  ST_UINT 128 
 int /*<<< orphan*/  menu_input_dialog_start (TYPE_2__*) ; 
 int /*<<< orphan*/ * menu_input_st_hex_cb ; 
 int /*<<< orphan*/ * menu_input_st_string_cb ; 
 int /*<<< orphan*/ * menu_input_st_uint_cb ; 
 int setting_get_type (TYPE_1__*) ; 

__attribute__((used)) static int setting_generic_action_ok_linefeed(rarch_setting_t *setting, bool wraparound)
{
   menu_input_ctx_line_t line;
   input_keyboard_line_complete_t cb = NULL;

   if (!setting)
      return -1;

   (void)wraparound;

   switch (setting_get_type(setting))
   {
      case ST_SIZE:
      case ST_UINT:
         cb = menu_input_st_uint_cb;
         break;
      case ST_HEX:
         cb = menu_input_st_hex_cb;
         break;
      case ST_STRING:
      case ST_STRING_OPTIONS:
         cb = menu_input_st_string_cb;
         break;
      default:
         break;
   }

   line.label         = setting->short_description;
   line.label_setting = setting->name;
   line.type          = 0;
   line.idx           = 0;
   line.cb            = cb;

   if (!menu_input_dialog_start(&line))
      return -1;

   return 0;
}