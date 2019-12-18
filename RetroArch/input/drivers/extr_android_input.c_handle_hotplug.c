#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct android_app {char* current_ime; } ;
typedef  int /*<<< orphan*/  name_buf ;
typedef  int /*<<< orphan*/  device_name ;
typedef  int /*<<< orphan*/  device_model ;
struct TYPE_6__ {scalar_t__ pads_connected; TYPE_1__* pad_states; } ;
typedef  TYPE_2__ android_input_t ;
struct TYPE_7__ {int /*<<< orphan*/  ident; } ;
struct TYPE_5__ {char* name; int id; int port; } ;

/* Variables and functions */
 int AINPUT_SOURCE_KEYBOARD ; 
 int DEFAULT_MAX_PADS ; 
 size_t MAX_NUM_KEYBOARDS ; 
 int /*<<< orphan*/  RARCH_ERR (char*) ; 
 int /*<<< orphan*/  RARCH_LOG (char*,char*,...) ; 
 TYPE_4__ android_joypad ; 
 int /*<<< orphan*/  engine_lookup_name (char*,int*,int*,int,int) ; 
 int /*<<< orphan*/  frontend_android_get_name (char*,int) ; 
 int /*<<< orphan*/  input_autoconfigure_connect (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int) ; 
 int* kbd_id ; 
 size_t kbd_num ; 
 int pad_id1 ; 
 int pad_id2 ; 
 int /*<<< orphan*/  string_is_empty (char*) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 
 scalar_t__ strstr (char*,char*) ; 

__attribute__((used)) static void handle_hotplug(android_input_t *android,
      struct android_app *android_app, int *port, int id,
      int source)
{
   char device_name[256];
   char device_model[256];
   char name_buf[256];
   int vendorId                 = 0;
   int productId                = 0;

   device_name[0] = device_model[0] = name_buf[0] = '\0';

   frontend_android_get_name(device_model, sizeof(device_model));

   RARCH_LOG("Device model: (%s).\n", device_model);

   if (*port > DEFAULT_MAX_PADS)
   {
      RARCH_ERR("Max number of pads reached.\n");
      return;
   }

   if (!engine_lookup_name(device_name, &vendorId,
            &productId, sizeof(device_name), id))
   {
      RARCH_ERR("Could not look up device name or IDs.\n");
      return;
   }

   /* FIXME - per-device hacks for NVidia Shield, Xperia Play and
    * similar devices
    *
    * These hacks depend on autoconf, but can work with user
    * created autoconfs properly
    */

   /* NVIDIA Shield Console
    * This is the most complicated example, the built-in controller
    * has an extra button that can't be used and a remote.
    *
    * We map the remote for navigation and overwrite whenever a
    * real controller is connected.
    * Also group the NVIDIA button on the controller with the
    * main controller inputs so it's usable. It's mapped to
    * menu by default
    *
    * The NVIDIA button is identified as "Virtual" device when first
    * pressed. CEC remote input is also identified as "Virtual" device.
    * If a virtual device is detected before a controller then it will
    * be assigned to port 0 as "SHIELD Virtual Controller". When a real
    * controller is detected it will overwrite the virtual controller
    * and be grouped with the NVIDIA button of the virtual device.
    *
    */
   if (strstr(device_model, "SHIELD Android TV") && (
      strstr(device_name, "Virtual") ||
      strstr(device_name, "NVIDIA Corporation NVIDIA Controller v01.0")))
   {
      /* only use the hack if the device is one of the built-in devices */
      RARCH_LOG("Special Device Detected: %s\n", device_model);
      {
#if 0
         RARCH_LOG("- Pads Mapped: %d\n- Device Name: %s\n- IDS: %d, %d, %d",
               android->pads_connected, device_name, id, pad_id1, pad_id2);
#endif
         /* remove the remote or virtual controller device if it is mapped */
         if (strstr(android->pad_states[0].name,"SHIELD Remote") ||
            strstr(android->pad_states[0].name,"SHIELD Virtual Controller"))
         {
            pad_id1 = -1;
            pad_id2 = -1;
            android->pads_connected = 0;
            *port = 0;
            strlcpy(name_buf, device_name, sizeof(name_buf));
         }

         /* if the actual controller has not been mapped yet,
          * then configure Virtual device for now */
         if (strstr(device_name, "Virtual") && android->pads_connected==0)
            strlcpy (name_buf, "SHIELD Virtual Controller", sizeof(name_buf));
         else
            strlcpy (name_buf, "NVIDIA SHIELD Controller", sizeof(name_buf));

         /* apply the hack only for the first controller
          * store the id for later use
         */
         if (strstr(device_name, "NVIDIA Corporation NVIDIA Controller v01.0")
               && android->pads_connected==0)
            pad_id1 = id;
         else if (strstr(device_name, "Virtual") && pad_id1 != -1)
         {
            id = pad_id1;
            return;
         }
      }
   }

   else if (strstr(device_model, "SHIELD") && (
      strstr(device_name, "Virtual") || strstr(device_name, "gpio") ||
      strstr(device_name, "NVIDIA Corporation NVIDIA Controller v01.01") ||
      strstr(device_name, "NVIDIA Corporation NVIDIA Controller v01.02")))
   {
      /* only use the hack if the device is one of the built-in devices */
      RARCH_LOG("Special Device Detected: %s\n", device_model);
      {
         if ( pad_id1 < 0 )
            pad_id1 = id;
         else
            pad_id2 = id;

         if ( pad_id2 > 0)
            return;
         strlcpy (name_buf, "NVIDIA SHIELD Portable", sizeof(name_buf));
      }
   }

   else if (strstr(device_model, "SHIELD") && (
      strstr(device_name, "Virtual") || strstr(device_name, "gpio") ||
      strstr(device_name, "NVIDIA Corporation NVIDIA Controller v01.03")))
   {
      /* only use the hack if the device is one of the built-in devices */
      RARCH_LOG("Special Device Detected: %s\n", device_model);
      {
         if (strstr(device_name, "NVIDIA Corporation NVIDIA Controller v01.03")
             && android->pads_connected==0)
            pad_id1 = id;
         else if (strstr(device_name, "Virtual") || strstr(device_name, "gpio"))
         {
            id = pad_id1;
            return;
         }
         strlcpy (name_buf, "NVIDIA SHIELD Gamepad", sizeof(name_buf));
      }
   }

   /* Other ATV Devices
    * Add other common ATV devices that will follow the Android
    * Gaempad convention as "Android Gamepad"
    */
    /* to-do: add DS4 on Bravia ATV */
   else if (strstr(device_name, "NVIDIA"))
      strlcpy (name_buf, "Android Gamepad", sizeof(name_buf));

   /* GPD XD
    * This is a simple hack, basically groups the "back"
    * button with the rest of the gamepad
    */
   else if (strstr(device_model, "XD") && (
      strstr(device_name, "Virtual") || strstr(device_name, "rk29-keypad") ||
      strstr(device_name,"Playstation3") || strstr(device_name,"XBOX")))
   {
      /* only use the hack if the device is one of the built-in devices */
      RARCH_LOG("Special Device Detected: %s\n", device_model);
      {
         if ( pad_id1 < 0 )
            pad_id1 = id;
         else
            pad_id2 = id;

         if ( pad_id2 > 0)
            return;

         strlcpy (name_buf, "GPD XD", sizeof(name_buf));
         *port = 0;
      }
   }

   /* XPERIA Play
    * This device is composed of two hid devices
    * We make it look like one device
    */
   else if(
            (
               strstr(device_model, "R800x") ||
               strstr(device_model, "R800at") ||
               strstr(device_model, "R800i") ||
               strstr(device_model, "R800a") ||
               strstr(device_model, "R800") ||
               strstr(device_model, "Xperia Play") ||
               strstr(device_model, "Play") ||
               strstr(device_model, "SO-01D")
            ) && (
               strstr(device_name, "keypad-game-zeus") ||
               strstr(device_name, "keypad-zeus") ||
               strstr(device_name, "Android Gamepad")
            )
         )
   {
      /* only use the hack if the device is one of the built-in devices */
      RARCH_LOG("Special Device Detected: %s\n", device_model);
      {
         if ( pad_id1 < 0 )
            pad_id1 = id;
         else
            pad_id2 = id;

         if ( pad_id2 > 0)
            return;

         strlcpy (name_buf, "XPERIA Play", sizeof(name_buf));
         *port = 0;
      }
   }

   /* ARCHOS Gamepad
    * This device is composed of two hid devices
    * We make it look like one device
    */
   else if (strstr(device_model, "ARCHOS GAMEPAD") && (
      strstr(device_name, "joy_key") || strstr(device_name, "joystick")))
   {
      /* only use the hack if the device is one of the built-in devices */
      RARCH_LOG("ARCHOS GAMEPAD Detected: %s\n", device_model);
      {
         if ( pad_id1 < 0 )
            pad_id1 = id;
         else
            pad_id2 = id;

         if ( pad_id2 > 0)
            return;

         strlcpy (name_buf, "ARCHOS GamePad", sizeof(name_buf));
         *port = 0;
      }
   }

   /* Amazon Fire TV & Fire stick */
   else if (strstr(device_model, "AFTB") || strstr(device_model, "AFTT") ||
           strstr(device_model, "AFTS") || strstr(device_model, "AFTM") ||
           strstr(device_model, "AFTRS"))
   {
      RARCH_LOG("Special Device Detected: %s\n", device_model);
      {
         /* always map remote to port #0 */
         if (strstr(device_name, "Amazon Fire TV Remote"))
         {
            android->pads_connected = 0;
            *port = 0;
            strlcpy(name_buf, device_name, sizeof(name_buf));
         }
         /* remove the remote when a gamepad enters */
         else if (strstr(android->pad_states[0].name,"Amazon Fire TV Remote"))
         {
            android->pads_connected = 0;
            *port = 0;
            strlcpy(name_buf, device_name, sizeof(name_buf));
         }
         else
            strlcpy(name_buf, device_name, sizeof(name_buf));
      }
   }

   /* Other uncommon devices
    * These are mostly remote control type devices, bind them always to port 0
    * And overwrite the binding whenever a controller button is pressed
    */
   else if (strstr(device_name, "Amazon Fire TV Remote")
         || strstr(device_name, "Nexus Remote")
         || strstr(device_name, "SHIELD Remote"))
   {
      android->pads_connected = 0;
      *port = 0;
      strlcpy(name_buf, device_name, sizeof(name_buf));
   }

   else if (strstr(device_name, "iControlPad-"))
      strlcpy(name_buf, "iControlPad HID Joystick profile", sizeof(name_buf));

   else if (strstr(device_name, "TTT THT Arcade console 2P USB Play"))
   {
      if (*port == 0)
         strlcpy(name_buf, "TTT THT Arcade (User 1)", sizeof(name_buf));
      else if (*port == 1)
         strlcpy(name_buf, "TTT THT Arcade (User 2)", sizeof(name_buf));
   }
   else if (strstr(device_name, "MOGA"))
      strlcpy(name_buf, "Moga IME", sizeof(name_buf));

   /* If device is keyboard only and didn't match any of the devices above
    * then assume it is a keyboard, register the id, and return unless the
    * maximum number of keyboards are already registered. */
   else if (source == AINPUT_SOURCE_KEYBOARD && kbd_num < MAX_NUM_KEYBOARDS)
   {
      kbd_id[kbd_num] = id;
      kbd_num++;
      return;
   }

   /* if device was not keyboard only, yet did not match any of the devices
    * then try to autoconfigure as gamepad based on device_name. */
   else if (!string_is_empty(device_name))
      strlcpy(name_buf, device_name, sizeof(name_buf));

   if (strstr(android_app->current_ime, "net.obsidianx.android.mogaime"))
      strlcpy(name_buf, android_app->current_ime, sizeof(name_buf));
   else if (strstr(android_app->current_ime, "com.ccpcreations.android.WiiUseAndroid"))
      strlcpy(name_buf, android_app->current_ime, sizeof(name_buf));
   else if (strstr(android_app->current_ime, "com.hexad.bluezime"))
      strlcpy(name_buf, android_app->current_ime, sizeof(name_buf));

   if (*port < 0)
      *port = android->pads_connected;

   input_autoconfigure_connect(
         name_buf,
         NULL,
         android_joypad.ident,
         *port,
         vendorId,
         productId);

   android->pad_states[android->pads_connected].id   = id;
   android->pad_states[android->pads_connected].port = *port;

   strlcpy(android->pad_states[*port].name, name_buf,
         sizeof(android->pad_states[*port].name));

   android->pads_connected++;
}