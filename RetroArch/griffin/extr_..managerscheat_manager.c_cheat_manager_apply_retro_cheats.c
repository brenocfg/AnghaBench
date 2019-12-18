#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned int address_mask; scalar_t__ handler; unsigned int address; int cheat_type; unsigned int value; unsigned int repeat_count; unsigned int repeat_add_to_address; scalar_t__ repeat_add_to_value; int /*<<< orphan*/  big_endian; int /*<<< orphan*/  memory_search_size; int /*<<< orphan*/  state; } ;
struct TYPE_3__ {unsigned int size; unsigned char* curr_memory_buf; unsigned int total_memory_size; TYPE_2__* cheats; int /*<<< orphan*/  big_endian; int /*<<< orphan*/  memory_initialized; } ;

/* Variables and functions */
 scalar_t__ CHEAT_HANDLER_TYPE_RETRO ; 
#define  CHEAT_TYPE_DECREASE_VALUE 134 
#define  CHEAT_TYPE_INCREASE_VALUE 133 
#define  CHEAT_TYPE_RUN_NEXT_IF_EQ 132 
#define  CHEAT_TYPE_RUN_NEXT_IF_GT 131 
#define  CHEAT_TYPE_RUN_NEXT_IF_LT 130 
#define  CHEAT_TYPE_RUN_NEXT_IF_NEQ 129 
#define  CHEAT_TYPE_SET_TO_VALUE 128 
 int /*<<< orphan*/  cheat_manager_apply_rumble (TYPE_2__*,unsigned int) ; 
 int /*<<< orphan*/  cheat_manager_initialize_memory (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cheat_manager_setup_search_meta (int /*<<< orphan*/ ,unsigned int*,unsigned int*,unsigned int*) ; 
 TYPE_1__ cheat_manager_state ; 
 unsigned int translate_address (unsigned int,unsigned char**) ; 

void cheat_manager_apply_retro_cheats(void)
{
   unsigned i;
   unsigned int offset;
   unsigned int mask           = 0;
   unsigned int bytes_per_item = 1;
   unsigned int bits           = 8;
   unsigned int curr_val       = 0;
   bool run_cheat              = true;

   if ((!cheat_manager_state.cheats))
      return;

   for (i = 0; i < cheat_manager_state.size; i++)
   {
      unsigned char *curr       = NULL;
      bool set_value            = false;
      unsigned int idx          = 0;
      unsigned int value_to_set = 0;
      unsigned int repeat_iter  = 0;
      unsigned int address_mask = cheat_manager_state.cheats[i].address_mask;

      if (cheat_manager_state.cheats[i].handler != CHEAT_HANDLER_TYPE_RETRO || !cheat_manager_state.cheats[i].state)
         continue;
      if (!cheat_manager_state.memory_initialized)
         cheat_manager_initialize_memory(NULL, false);

      /* If we're still not initialized, something
       * must have gone wrong - just bail */
      if (!cheat_manager_state.memory_initialized)
         return;

      if (!run_cheat)
      {
         run_cheat = true;
         continue;
      }
      cheat_manager_setup_search_meta(cheat_manager_state.cheats[i].memory_search_size, &bytes_per_item, &mask, &bits);

      curr   = cheat_manager_state.curr_memory_buf;
      idx    = cheat_manager_state.cheats[i].address;

      offset = translate_address(idx, &curr);

      switch (bytes_per_item)
      {
         case 2:
            curr_val = cheat_manager_state.big_endian ?
               (*(curr + idx - offset) * 256) + *(curr + idx + 1 - offset) :
               *(curr + idx - offset) + (*(curr + idx + 1 - offset) * 256);
            break;
         case 4:
            curr_val = cheat_manager_state.big_endian ?
               (*(curr + idx - offset) * 256 * 256 * 256) + (*(curr + idx + 1 - offset) * 256 * 256) + (*(curr + idx + 2 - offset) * 256) + *(curr + idx + 3 - offset) :
               *(curr + idx - offset) + (*(curr + idx + 1 - offset) * 256) + (*(curr + idx + 2 - offset) * 256 * 256) + (*(curr + idx + 3 - offset) * 256 * 256 * 256);
            break;
         case 1:
         default:
            curr_val = *(curr + idx - offset);
            break;
      }

      cheat_manager_apply_rumble(&cheat_manager_state.cheats[i], curr_val);

      switch (cheat_manager_state.cheats[i].cheat_type)
      {
         case CHEAT_TYPE_SET_TO_VALUE:
            set_value = true;
            value_to_set = cheat_manager_state.cheats[i].value;
            break;
         case CHEAT_TYPE_INCREASE_VALUE:
            set_value = true;
            value_to_set = curr_val + cheat_manager_state.cheats[i].value;
            break;
         case CHEAT_TYPE_DECREASE_VALUE:
            set_value = true;
            value_to_set = curr_val - cheat_manager_state.cheats[i].value;
            break;
         case CHEAT_TYPE_RUN_NEXT_IF_EQ:
            if (!(curr_val == cheat_manager_state.cheats[i].value))
               run_cheat = false;
            break;
         case CHEAT_TYPE_RUN_NEXT_IF_NEQ:
            if (!(curr_val != cheat_manager_state.cheats[i].value))
               run_cheat = false;
            break;
         case CHEAT_TYPE_RUN_NEXT_IF_LT:
            if (!(cheat_manager_state.cheats[i].value < curr_val))
               run_cheat = false;
            break;
         case CHEAT_TYPE_RUN_NEXT_IF_GT:
            if (!(cheat_manager_state.cheats[i].value > curr_val))
               run_cheat = false;
            break;
      }

      if (set_value)
      {
         for (repeat_iter = 1; repeat_iter <= cheat_manager_state.cheats[i].repeat_count; repeat_iter++)
         {
            switch (bytes_per_item)
            {
               case 2:
                  if (cheat_manager_state.cheats[i].big_endian)
                  {
                     *(curr + idx - offset) = (value_to_set >> 8) & 0xFF;
                     *(curr + idx + 1 - offset) = value_to_set & 0xFF;
                  }
                  else
                  {
                     *(curr + idx - offset) = value_to_set & 0xFF;
                     *(curr + idx + 1 - offset) = (value_to_set >> 8) & 0xFF;
                  }
                  break;
               case 4:
                  if (cheat_manager_state.cheats[i].big_endian)
                  {
                     *(curr + idx - offset) = (value_to_set >> 24) & 0xFF;
                     *(curr + idx + 1 - offset) = (value_to_set >> 16) & 0xFF;
                     *(curr + idx + 2 - offset) = (value_to_set >> 8) & 0xFF;
                     *(curr + idx + 3 - offset) = value_to_set & 0xFF;
                  }
                  else
                  {
                     *(curr + idx - offset) = value_to_set & 0xFF;
                     *(curr + idx + 1 - offset) = (value_to_set >> 8) & 0xFF;
                     *(curr + idx + 2 - offset) = (value_to_set >> 16) & 0xFF;
                     *(curr + idx + 3 - offset) = (value_to_set >> 24) & 0xFF;
                  }
                  break;
               case 1:
                  if (bits < 8)
                  {
                     unsigned bitpos;
                     unsigned char val = *(curr + idx - offset);

                     for (bitpos = 0; bitpos < 8; bitpos++)
                     {
                        if ((address_mask >> bitpos) & 0x01)
                        {
                           mask = (~(1 << bitpos) & 0xFF);
                           /* Clear current bit value */
                           val = val & mask;
                           /* Inject cheat bit value */
                           val = val | (((value_to_set >> bitpos) & 0x01) << bitpos);
                        }
                     }

                     *(curr + idx - offset) = val;
                  }
                  else
                     *(curr + idx - offset) = value_to_set & 0xFF;
                  break;
               default:
                  *(curr + idx - offset) = value_to_set & 0xFF;
                  break;
            }

            value_to_set += cheat_manager_state.cheats[i].repeat_add_to_value;

            if (mask != 0)
               value_to_set = value_to_set % mask;

            if (bits < 8)
            {
               unsigned int bit_iter;
               for (bit_iter = 0; bit_iter < cheat_manager_state.cheats[i].repeat_add_to_address; bit_iter++)
               {
                  address_mask = (address_mask << mask) & 0xFF;

                  if (address_mask == 0)
                  {
                     address_mask = mask;
                     idx++;
                  }
               }
            }
            else
               idx += (cheat_manager_state.cheats[i].repeat_add_to_address * bytes_per_item);

            idx = idx % cheat_manager_state.total_memory_size;

            offset = translate_address(idx, &curr);
         }
      }
   }
}