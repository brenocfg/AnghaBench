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
struct vote_count {size_t* votes; } ;
struct delta_frame {TYPE_2__** real_input; } ;
struct TYPE_7__ {int* device_share_modes; } ;
typedef  TYPE_1__ netplay_t ;
typedef  TYPE_2__* netplay_input_state_t ;
struct TYPE_8__ {size_t size; int client_num; int* data; int /*<<< orphan*/  used; struct TYPE_8__* next; } ;

/* Variables and functions */
 size_t MAX_CLIENTS ; 
 int NETPLAY_SHARE_DIGITAL_BITS ; 
 int NETPLAY_SHARE_DIGITAL_VOTE ; 
#define  NETPLAY_SHARE_DIGITAL_XOR 128 
 TYPE_2__* netplay_device_client_state (TYPE_1__*,struct delta_frame*,size_t,size_t) ; 

__attribute__((used)) static void netplay_merge_digital(netplay_t *netplay,
      netplay_input_state_t resstate, struct delta_frame *simframe,
      uint32_t device, uint32_t clients, const uint32_t *digital)
{
   netplay_input_state_t simstate;
   uint32_t word, bit, client;
   uint8_t share_mode = netplay->device_share_modes[device]
      & NETPLAY_SHARE_DIGITAL_BITS;

   /* Make sure all real clients are accounted for */
   for (simstate = simframe->real_input[device];
         simstate; simstate = simstate->next)
   {
      if (!simstate->used || simstate->size != resstate->size)
         continue;
      clients |= 1<<simstate->client_num;
   }

   if (share_mode == NETPLAY_SHARE_DIGITAL_VOTE)
   {
      unsigned i, j;
      /* This just assumes we have no more than
       * three words, will need to be adjusted for new devices */
      struct vote_count votes[3];
      /* Vote mode requires counting all the bits */
      uint32_t client_count      = 0;

      for (i = 0; i < 3; i++)
         for (j = 0; j < 32; j++)
            votes[i].votes[j] = 0;

      for (client = 0; client < MAX_CLIENTS; client++)
      {
         if (!(clients & (1<<client)))
            continue;

         simstate = netplay_device_client_state(
               netplay, simframe, device, client);

         if (!simstate)
            continue;
         client_count++;

         for (word = 0; word < resstate->size; word++)
         {
            if (!digital[word])
               continue;
            for (bit = 0; bit < 32; bit++)
            {
               if (!(digital[word] & (1<<bit)))
                  continue;
               if (simstate->data[word] & (1<<bit))
                  votes[word].votes[bit]++;
            }
         }
      }

      /* Now count all the bits */
      client_count /= 2;
      for (word = 0; word < resstate->size; word++)
      {
         for (bit = 0; bit < 32; bit++)
         {
            if (votes[word].votes[bit] > client_count)
               resstate->data[word] |= (1<<bit);
         }
      }
   }
   else /* !VOTE */
   {
      for (client = 0; client < MAX_CLIENTS; client++)
      {
         if (!(clients & (1<<client)))
            continue;
         simstate = netplay_device_client_state(
               netplay, simframe, device, client);

         if (!simstate)
            continue;
         for (word = 0; word < resstate->size; word++)
         {
            uint32_t part;
            if (!digital[word])
               continue;
            part = simstate->data[word];

            if (digital[word] == (uint32_t) -1)
            {
               /* Combine the whole word */
               switch (share_mode)
               {
                  case NETPLAY_SHARE_DIGITAL_XOR:
                     resstate->data[word] ^= part;
                     break;
                  default:
                     resstate->data[word] |= part;
               }

            }
            else /* !whole word */
            {
               for (bit = 0; bit < 32; bit++)
               {
                  if (!(digital[word] & (1<<bit)))
                     continue;
                  switch (share_mode)
                  {
                     case NETPLAY_SHARE_DIGITAL_XOR:
                        resstate->data[word] ^= part & (1<<bit);
                        break;
                     default:
                        resstate->data[word] |= part & (1<<bit);
                  }
               }
            }
         }
      }

   }
}