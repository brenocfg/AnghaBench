#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {void* boolean; void* integer; void* unsigned_integer; void* sizet; void* fraction; void* keybind; void* string; } ;
struct TYPE_6__ {TYPE_2__ target; } ;
struct TYPE_8__ {TYPE_1__ value; } ;
typedef  TYPE_3__ rarch_setting_t ;

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
 int setting_get_type (TYPE_3__*) ; 

__attribute__((used)) static void *setting_get_ptr(rarch_setting_t *setting)
{
   if (!setting)
      return NULL;

   switch (setting_get_type(setting))
   {
      case ST_BOOL:
         return setting->value.target.boolean;
      case ST_INT:
         return setting->value.target.integer;
      case ST_UINT:
         return setting->value.target.unsigned_integer;
      case ST_SIZE:
         return setting->value.target.sizet;
      case ST_FLOAT:
         return setting->value.target.fraction;
      case ST_BIND:
         return setting->value.target.keybind;
      case ST_STRING:
      case ST_STRING_OPTIONS:
      case ST_PATH:
      case ST_DIR:
         return setting->value.target.string;
      default:
         break;
   }

   return NULL;
}