#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  enum retro_sensor_action { ____Placeholder_retro_sensor_action } retro_sensor_action ;
struct TYPE_3__ {int* device_capability; } ;
typedef  TYPE_1__ CellPadInfo2 ;

/* Variables and functions */
 int CELL_PAD_CAPABILITY_SENSOR_MODE ; 
 int /*<<< orphan*/  CELL_PAD_SETTING_SENSOR_ON ; 
#define  RETRO_SENSOR_ACCELEROMETER_DISABLE 129 
#define  RETRO_SENSOR_ACCELEROMETER_ENABLE 128 
 int /*<<< orphan*/  cellPadGetInfo2 (TYPE_1__*) ; 
 int /*<<< orphan*/  cellPadSetPortSetting (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool ps3_input_set_sensor_state(void *data, unsigned port,
      enum retro_sensor_action action, unsigned event_rate)
{
   CellPadInfo2 pad_info;
   (void)event_rate;

   switch (action)
   {
      case RETRO_SENSOR_ACCELEROMETER_ENABLE:
         cellPadGetInfo2(&pad_info);
         if ((pad_info.device_capability[port]
                  & CELL_PAD_CAPABILITY_SENSOR_MODE)
               != CELL_PAD_CAPABILITY_SENSOR_MODE)
            return false;

         cellPadSetPortSetting(port, CELL_PAD_SETTING_SENSOR_ON);
         return true;
      case RETRO_SENSOR_ACCELEROMETER_DISABLE:
         cellPadSetPortSetting(port, 0);
         return true;

      default:
         return false;
   }
}