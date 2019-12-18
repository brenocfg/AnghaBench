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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct delta_frame {TYPE_2__** resolved_input; } ;
struct TYPE_4__ {size_t replay_ptr; size_t run_ptr; unsigned int* config_devices; struct delta_frame* buffer; scalar_t__ is_replay; } ;
typedef  TYPE_1__ netplay_t ;
typedef  TYPE_2__* netplay_input_state_t ;
typedef  int const int16_t ;
struct TYPE_5__ {scalar_t__ size; int* data; int /*<<< orphan*/  used; } ;

/* Variables and functions */
 unsigned int MAX_INPUT_DEVICES ; 
 unsigned int NETPLAY_KEY_UNKNOWN ; 
#define  RETRO_DEVICE_ANALOG 132 
 unsigned int RETRO_DEVICE_ID_JOYPAD_MASK ; 
 unsigned int RETRO_DEVICE_ID_MOUSE_Y ; 
#define  RETRO_DEVICE_JOYPAD 131 
#define  RETRO_DEVICE_KEYBOARD 130 
#define  RETRO_DEVICE_LIGHTGUN 129 
 unsigned int RETRO_DEVICE_MASK ; 
#define  RETRO_DEVICE_MOUSE 128 
 unsigned int netplay_key_hton (unsigned int) ; 

__attribute__((used)) static int16_t netplay_input_state(netplay_t *netplay,
      unsigned port, unsigned device,
      unsigned idx, unsigned id)
{
   size_t ptr = netplay->is_replay ?
      netplay->replay_ptr : netplay->run_ptr;
   struct delta_frame *delta;
   netplay_input_state_t istate;

   const uint32_t *curr_input_state = NULL;

   if (port >= MAX_INPUT_DEVICES)
      return 0;

   /* If the port doesn't seem to correspond to the device, "correct" it. This
    * is common with devices that typically only have one instance, such as
    * keyboards, mice and lightguns. */
   if (device != RETRO_DEVICE_JOYPAD &&
       (netplay->config_devices[port]&RETRO_DEVICE_MASK) != device)
   {
      for (port = 0; port < MAX_INPUT_DEVICES; port++)
      {
         if ((netplay->config_devices[port]&RETRO_DEVICE_MASK) == device)
            break;
      }
      if (port == MAX_INPUT_DEVICES)
         return 0;
   }

   delta = &netplay->buffer[ptr];
   istate = delta->resolved_input[port];
   if (!istate || !istate->used)
      return 0;

   if (istate->size == 0)
      return 0;
   curr_input_state = istate->data;

   switch (device)
   {
      case RETRO_DEVICE_JOYPAD:
         if (id == RETRO_DEVICE_ID_JOYPAD_MASK)
            return curr_input_state[0];
         return ((1 << id) & curr_input_state[0]) ? 1 : 0;

      case RETRO_DEVICE_ANALOG:
         {
            uint32_t state;
            if (istate->size != 3)
               return 0;
            state = curr_input_state[1 + idx];
            return (int16_t)(uint16_t)(state >> (id * 16));
         }

      case RETRO_DEVICE_MOUSE:
      case RETRO_DEVICE_LIGHTGUN:
         if (istate->size != 2)
            return 0;
         if (id <= RETRO_DEVICE_ID_MOUSE_Y)
            return (int16_t)(uint16_t)(curr_input_state[1] >> (id * 16));
         return ((1 << id) & curr_input_state[0]) ? 1 : 0;
      case RETRO_DEVICE_KEYBOARD:
         {
            unsigned word, bit;
            unsigned key = netplay_key_hton(id);
            if (key == NETPLAY_KEY_UNKNOWN)
               return 0;
            word = key / 32;
            bit  = key % 32;
            if (word <= istate->size)
               return ((1U<<bit) & curr_input_state[word]) ? 1 : 0;
            return 0;
         }
      default:
         return 0;
   }
}