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
typedef  enum rarch_override_setting { ____Placeholder_rarch_override_setting } rarch_override_setting ;

/* Variables and functions */
 int /*<<< orphan*/  BIT256_CLEAR (int /*<<< orphan*/ ,unsigned int) ; 
#define  RARCH_OVERRIDE_SETTING_BPS_PREF 143 
#define  RARCH_OVERRIDE_SETTING_IPS_PREF 142 
#define  RARCH_OVERRIDE_SETTING_LIBRETRO 141 
#define  RARCH_OVERRIDE_SETTING_LIBRETRO_DEVICE 140 
#define  RARCH_OVERRIDE_SETTING_LIBRETRO_DIRECTORY 139 
#define  RARCH_OVERRIDE_SETTING_LOG_TO_FILE 138 
#define  RARCH_OVERRIDE_SETTING_NETPLAY_CHECK_FRAMES 137 
#define  RARCH_OVERRIDE_SETTING_NETPLAY_IP_ADDRESS 136 
#define  RARCH_OVERRIDE_SETTING_NETPLAY_IP_PORT 135 
#define  RARCH_OVERRIDE_SETTING_NETPLAY_MODE 134 
#define  RARCH_OVERRIDE_SETTING_NETPLAY_STATELESS_MODE 133 
#define  RARCH_OVERRIDE_SETTING_NONE 132 
#define  RARCH_OVERRIDE_SETTING_SAVE_PATH 131 
#define  RARCH_OVERRIDE_SETTING_STATE_PATH 130 
#define  RARCH_OVERRIDE_SETTING_UPS_PREF 129 
#define  RARCH_OVERRIDE_SETTING_VERBOSITY 128 
 int has_set_bps_pref ; 
 int has_set_ips_pref ; 
 int has_set_libretro ; 
 int /*<<< orphan*/  has_set_libretro_device ; 
 int has_set_libretro_directory ; 
 int has_set_log_to_file ; 
 int has_set_netplay_check_frames ; 
 int has_set_netplay_ip_address ; 
 int has_set_netplay_ip_port ; 
 int has_set_netplay_mode ; 
 int has_set_netplay_stateless_mode ; 
 int has_set_save_path ; 
 int has_set_state_path ; 
 int has_set_ups_pref ; 
 int has_set_verbosity ; 

void retroarch_override_setting_unset(enum rarch_override_setting enum_idx, void *data)
{
   switch (enum_idx)
   {
      case RARCH_OVERRIDE_SETTING_LIBRETRO_DEVICE:
         {
            unsigned *val = (unsigned*)data;
            if (val)
            {
               unsigned bit = *val;
               BIT256_CLEAR(has_set_libretro_device, bit);
            }
         }
         break;
      case RARCH_OVERRIDE_SETTING_VERBOSITY:
         has_set_verbosity = false;
         break;
      case RARCH_OVERRIDE_SETTING_LIBRETRO:
         has_set_libretro = false;
         break;
      case RARCH_OVERRIDE_SETTING_LIBRETRO_DIRECTORY:
         has_set_libretro_directory = false;
         break;
      case RARCH_OVERRIDE_SETTING_SAVE_PATH:
         has_set_save_path = false;
         break;
      case RARCH_OVERRIDE_SETTING_STATE_PATH:
         has_set_state_path = false;
         break;
      case RARCH_OVERRIDE_SETTING_NETPLAY_MODE:
         has_set_netplay_mode = false;
         break;
      case RARCH_OVERRIDE_SETTING_NETPLAY_IP_ADDRESS:
         has_set_netplay_ip_address = false;
         break;
      case RARCH_OVERRIDE_SETTING_NETPLAY_IP_PORT:
         has_set_netplay_ip_port = false;
         break;
      case RARCH_OVERRIDE_SETTING_NETPLAY_STATELESS_MODE:
         has_set_netplay_stateless_mode = false;
         break;
      case RARCH_OVERRIDE_SETTING_NETPLAY_CHECK_FRAMES:
         has_set_netplay_check_frames = false;
         break;
      case RARCH_OVERRIDE_SETTING_UPS_PREF:
         has_set_ups_pref = false;
         break;
      case RARCH_OVERRIDE_SETTING_BPS_PREF:
         has_set_bps_pref = false;
         break;
      case RARCH_OVERRIDE_SETTING_IPS_PREF:
         has_set_ips_pref = false;
         break;
      case RARCH_OVERRIDE_SETTING_LOG_TO_FILE:
         has_set_log_to_file = false;
         break;
      case RARCH_OVERRIDE_SETTING_NONE:
      default:
         break;
   }
}