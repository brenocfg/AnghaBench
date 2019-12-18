#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  size_t uint32_t ;
typedef  scalar_t__ uint16_t ;
struct delta_frame {TYPE_2__** real_input; } ;
struct TYPE_7__ {int* device_share_modes; } ;
typedef  TYPE_1__ netplay_t ;
typedef  TYPE_2__* netplay_input_state_t ;
typedef  size_t int32_t ;
typedef  size_t int16_t ;
struct TYPE_8__ {scalar_t__ size; int client_num; int* data; int /*<<< orphan*/  used; struct TYPE_8__* next; } ;

/* Variables and functions */
 size_t MAX_CLIENTS ; 
#define  NETPLAY_SHARE_ANALOG_AVERAGE 128 
 int NETPLAY_SHARE_ANALOG_BITS ; 
 int /*<<< orphan*/  abs (size_t) ; 
 TYPE_2__* netplay_device_client_state (TYPE_1__*,struct delta_frame*,size_t,size_t) ; 

__attribute__((used)) static void merge_analog_part(netplay_t *netplay,
      netplay_input_state_t resstate, struct delta_frame *simframe,
      uint32_t device, uint32_t clients, uint32_t word, uint8_t bit)
{
   netplay_input_state_t simstate;
   uint32_t client, client_count = 0;
   uint8_t share_mode            = netplay->device_share_modes[device]
      & NETPLAY_SHARE_ANALOG_BITS;
   int32_t value                 = 0, new_value;

   /* Make sure all real clients are accounted for */
   for (simstate = simframe->real_input[device]; simstate; simstate = simstate->next)
   {
      if (!simstate->used || simstate->size != resstate->size)
         continue;
      clients |= 1<<simstate->client_num;
   }

   for (client = 0; client < MAX_CLIENTS; client++)
   {
      if (!(clients & (1<<client)))
         continue;
      simstate = netplay_device_client_state(
            netplay, simframe, device, client);
      if (!simstate)
         continue;
      client_count++;
      new_value = (int16_t) ((simstate->data[word]>>bit) & 0xFFFF);
      switch (share_mode)
      {
         case NETPLAY_SHARE_ANALOG_AVERAGE:
            value += (int32_t) new_value;
            break;
         default:
            if (abs(new_value) > abs(value) ||
                (abs(new_value) == abs(value) && new_value > value))
               value = new_value;
      }
   }

   if (share_mode == NETPLAY_SHARE_ANALOG_AVERAGE)
      if (client_count > 0) /* Prevent potential divide by zero */
         value /= client_count;

   resstate->data[word] |= ((uint32_t) (uint16_t) value) << bit;
}