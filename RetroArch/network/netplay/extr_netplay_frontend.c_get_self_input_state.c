#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int uint16_t ;
struct netplay_connection {scalar_t__ mode; scalar_t__ active; } ;
struct delta_frame {int have_local; int* have_real; int /*<<< orphan*/ * real_input; } ;
typedef  int /*<<< orphan*/  (* retro_input_state_t ) (int,int const,unsigned int,unsigned int) ;
struct TYPE_10__ {int /*<<< orphan*/  (* state_cb ) (int,int const,unsigned int,unsigned int) ;} ;
struct TYPE_11__ {size_t self_ptr; int self_devices; int* config_devices; scalar_t__ self_mode; size_t self_client_num; unsigned int connections_size; scalar_t__ is_server; struct netplay_connection* connections; int /*<<< orphan*/  self_frame_count; scalar_t__* read_frame_count; int /*<<< orphan*/ * read_ptr; TYPE_1__ cbs; struct delta_frame* buffer; } ;
typedef  TYPE_2__ netplay_t ;
typedef  TYPE_3__* netplay_input_state_t ;
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_12__ {int* data; unsigned int size; } ;

/* Variables and functions */
 size_t MAX_CLIENTS ; 
 int MAX_INPUT_DEVICES ; 
 scalar_t__ NETPLAY_CONNECTION_CONNECTED ; 
 scalar_t__ NETPLAY_CONNECTION_PLAYING ; 
 scalar_t__ NETPLAY_CONNECTION_SLAVE ; 
 unsigned int NETPLAY_KEY_LAST ; 
 int /*<<< orphan*/  NEXT_PTR (size_t) ; 
#define  RETRO_DEVICE_ANALOG 132 
 unsigned int RETRO_DEVICE_ID_JOYPAD_R3 ; 
 int /*<<< orphan*/  RETRO_DEVICE_ID_LIGHTGUN_START ; 
 int /*<<< orphan*/  RETRO_DEVICE_ID_MOUSE_HORIZ_WHEELDOWN ; 
#define  RETRO_DEVICE_JOYPAD 131 
#define  RETRO_DEVICE_KEYBOARD 130 
#define  RETRO_DEVICE_LIGHTGUN 129 
 int RETRO_DEVICE_MASK ; 
#define  RETRO_DEVICE_MOUSE 128 
 int /*<<< orphan*/  input_driver_is_libretro_input_blocked () ; 
 int /*<<< orphan*/  netplay_delayed_state_change (TYPE_2__*) ; 
 int /*<<< orphan*/  netplay_delta_frame_ready (TYPE_2__*,struct delta_frame*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netplay_expected_input_size (TYPE_2__*,int) ; 
 TYPE_3__* netplay_input_state_for (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int,int) ; 
 unsigned int netplay_key_ntoh (unsigned int) ; 
 int /*<<< orphan*/  netplay_send_cur_input (TYPE_2__*,struct netplay_connection*) ; 

__attribute__((used)) static bool get_self_input_state(netplay_t *netplay)
{
   unsigned i;
   struct delta_frame *ptr        = &netplay->buffer[netplay->self_ptr];
   netplay_input_state_t istate   = NULL;
   uint32_t devices, used_devices = 0, devi, dev_type, local_device;

   if (!netplay_delta_frame_ready(netplay, ptr, netplay->self_frame_count))
      return false;

   /* We've already read this frame! */
   if (ptr->have_local)
      return true;

   devices      = netplay->self_devices;
   used_devices = 0;

   for (devi = 0; devi < MAX_INPUT_DEVICES; devi++)
   {
      if (!(devices & (1<<devi)))
         continue;

      /* Find an appropriate local device */
      dev_type = netplay->config_devices[devi]&RETRO_DEVICE_MASK;

      for (local_device = 0; local_device < MAX_INPUT_DEVICES; local_device++)
      {
         if (used_devices & (1<<local_device))
            continue;
         if ((netplay->config_devices[local_device]&RETRO_DEVICE_MASK) == dev_type)
            break;
      }

      if (local_device == MAX_INPUT_DEVICES)
         local_device = 0;
      used_devices |= (1<<local_device);

      istate = netplay_input_state_for(&ptr->real_input[devi],
            /* If we're a slave, we write our own input to MAX_CLIENTS to keep it separate */
            (netplay->self_mode==NETPLAY_CONNECTION_SLAVE)?MAX_CLIENTS:netplay->self_client_num,
            netplay_expected_input_size(netplay, 1 << devi),
            true, false);
      if (!istate)
         continue; /* FIXME: More severe? */

      /* First frame we always give zero input since relying on
       * input from first frame screws up when we use -F 0. */
      if (!input_driver_is_libretro_input_blocked() && netplay->self_frame_count > 0)
      {
         uint32_t *state        = istate->data;
         retro_input_state_t cb = netplay->cbs.state_cb;
         unsigned dtype         = netplay->config_devices[devi]&RETRO_DEVICE_MASK;

         switch (dtype)
         {
            case RETRO_DEVICE_ANALOG:
               for (i = 0; i < 2; i++)
               {
                  int16_t tmp_x = cb(local_device,
                        RETRO_DEVICE_ANALOG, (unsigned)i, 0);
                  int16_t tmp_y = cb(local_device,
                        RETRO_DEVICE_ANALOG, (unsigned)i, 1);
                  state[1 + i] = (uint16_t)tmp_x | (((uint16_t)tmp_y) << 16);
               }
               /* no break */

            case RETRO_DEVICE_JOYPAD:
               for (i = 0; i <= RETRO_DEVICE_ID_JOYPAD_R3; i++)
               {
                  int16_t tmp = cb(local_device,
                        RETRO_DEVICE_JOYPAD, 0, (unsigned)i);
                  state[0] |= tmp ? 1 << i : 0;
               }
               break;

            case RETRO_DEVICE_MOUSE:
            case RETRO_DEVICE_LIGHTGUN:
            {
               int16_t tmp_x = cb(local_device, dtype, 0, 0);
               int16_t tmp_y = cb(local_device, dtype, 0, 1);
               state[1] = (uint16_t)tmp_x | (((uint16_t)tmp_y) << 16);
               for (i = 2;
                     i <= (unsigned)((dtype == RETRO_DEVICE_MOUSE) ?
                           RETRO_DEVICE_ID_MOUSE_HORIZ_WHEELDOWN :
                           RETRO_DEVICE_ID_LIGHTGUN_START);
                     i++)
               {
                  int16_t tmp = cb(local_device, dtype, 0,
                        (unsigned) i);
                  state[0] |= tmp ? 1 << i : 0;
               }
               break;
            }

            case RETRO_DEVICE_KEYBOARD:
            {
               unsigned key, word = 0, bit = 1;
               for (key = 1; key < NETPLAY_KEY_LAST; key++)
               {
                  state[word] |=
                        cb(local_device, RETRO_DEVICE_KEYBOARD, 0, netplay_key_ntoh(key)) ?
                              (1U << bit) : 0;
                  bit++;
                  if (bit >= 32)
                  {
                     bit = 0;
                     word++;
                     if (word >= istate->size)
                        break;
                  }
               }
               break;
            }
         }
      }
   }

   ptr->have_local = true;
   if (netplay->self_mode == NETPLAY_CONNECTION_PLAYING)
   {
      ptr->have_real[netplay->self_client_num] = true;
      netplay->read_ptr[netplay->self_client_num] = NEXT_PTR(netplay->self_ptr);
      netplay->read_frame_count[netplay->self_client_num] = netplay->self_frame_count + 1;
   }

   /* And send this input to our peers */
   for (i = 0; i < netplay->connections_size; i++)
   {
      struct netplay_connection *connection = &netplay->connections[i];
      if (connection->active && connection->mode >= NETPLAY_CONNECTION_CONNECTED)
         netplay_send_cur_input(netplay, &netplay->connections[i]);
   }

   /* Handle any delayed state changes */
   if (netplay->is_server)
      netplay_delayed_state_change(netplay);

   return true;
}