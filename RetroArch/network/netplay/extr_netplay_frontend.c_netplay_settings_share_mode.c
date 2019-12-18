#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_4__ {int netplay_share_digital; int netplay_share_analog; } ;
struct TYPE_5__ {TYPE_1__ uints; } ;
typedef  TYPE_2__ settings_t ;

/* Variables and functions */
 int /*<<< orphan*/  NETPLAY_SHARE_ANALOG_AVERAGE ; 
 int /*<<< orphan*/  NETPLAY_SHARE_ANALOG_MAX ; 
 int /*<<< orphan*/  NETPLAY_SHARE_DIGITAL_OR ; 
 int /*<<< orphan*/  NETPLAY_SHARE_DIGITAL_VOTE ; 
 int /*<<< orphan*/  NETPLAY_SHARE_DIGITAL_XOR ; 
 int /*<<< orphan*/  NETPLAY_SHARE_NO_PREFERENCE ; 
#define  RARCH_NETPLAY_SHARE_ANALOG_AVERAGE 132 
#define  RARCH_NETPLAY_SHARE_ANALOG_MAX 131 
#define  RARCH_NETPLAY_SHARE_DIGITAL_OR 130 
#define  RARCH_NETPLAY_SHARE_DIGITAL_VOTE 129 
#define  RARCH_NETPLAY_SHARE_DIGITAL_XOR 128 
 TYPE_2__* config_get_ptr () ; 

uint8_t netplay_settings_share_mode(void)
{
   settings_t *settings = config_get_ptr();
   uint8_t share_mode = 0;

   if (settings->uints.netplay_share_digital
         || settings->uints.netplay_share_analog)
   {
      switch (settings->uints.netplay_share_digital)
      {
         case RARCH_NETPLAY_SHARE_DIGITAL_OR:
            share_mode |= NETPLAY_SHARE_DIGITAL_OR;
            break;
         case RARCH_NETPLAY_SHARE_DIGITAL_XOR:
            share_mode |= NETPLAY_SHARE_DIGITAL_XOR;
            break;
         case RARCH_NETPLAY_SHARE_DIGITAL_VOTE:
            share_mode |= NETPLAY_SHARE_DIGITAL_VOTE;
            break;
         default:
            share_mode |= NETPLAY_SHARE_NO_PREFERENCE;
      }
      switch (settings->uints.netplay_share_analog)
      {
         case RARCH_NETPLAY_SHARE_ANALOG_MAX:
            share_mode |= NETPLAY_SHARE_ANALOG_MAX;
            break;
         case RARCH_NETPLAY_SHARE_ANALOG_AVERAGE:
            share_mode |= NETPLAY_SHARE_ANALOG_AVERAGE;
            break;
         default:
            share_mode |= NETPLAY_SHARE_NO_PREFERENCE;
      }
   }

   return share_mode;
}