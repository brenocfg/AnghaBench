#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  enum cheat_match_action_type { ____Placeholder_cheat_match_action_type } cheat_match_action_type ;
struct TYPE_2__ {unsigned char* curr_memory_buf; unsigned char* prev_memory_buf; int num_matches; scalar_t__ num_memory_buffers; unsigned int total_memory_size; unsigned int* matches; int /*<<< orphan*/  big_endian; int /*<<< orphan*/  search_bit_size; } ;

/* Variables and functions */
#define  CHEAT_MATCH_ACTION_TYPE_BROWSE 131 
#define  CHEAT_MATCH_ACTION_TYPE_COPY 130 
#define  CHEAT_MATCH_ACTION_TYPE_DELETE 129 
#define  CHEAT_MATCH_ACTION_TYPE_VIEW 128 
 int /*<<< orphan*/  MESSAGE_QUEUE_CATEGORY_INFO ; 
 int /*<<< orphan*/  MESSAGE_QUEUE_ICON_DEFAULT ; 
 int /*<<< orphan*/  MSG_CHEAT_SEARCH_ADD_MATCH_FAIL ; 
 int /*<<< orphan*/  MSG_CHEAT_SEARCH_ADD_MATCH_SUCCESS ; 
 int /*<<< orphan*/  MSG_CHEAT_SEARCH_DELETE_MATCH_SUCCESS ; 
 int /*<<< orphan*/  cheat_manager_add_new_code (int /*<<< orphan*/ ,unsigned int,int,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  cheat_manager_setup_search_meta (int /*<<< orphan*/ ,unsigned int*,unsigned int*,unsigned int*) ; 
 TYPE_1__ cheat_manager_state ; 
 int /*<<< orphan*/  memset (unsigned int*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  msg_hash_to_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  runloop_msg_queue_push (int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int translate_address (unsigned int,unsigned char**) ; 

void cheat_manager_match_action(enum cheat_match_action_type match_action, unsigned int target_match_idx, unsigned int *address, unsigned int *address_mask,
      unsigned int *prev_value, unsigned int *curr_value)
{
   unsigned int byte_part;
   unsigned int idx;
   unsigned int start_idx;
   unsigned int mask = 0;
   unsigned int bytes_per_item = 1;
   unsigned int bits = 8;
   unsigned int curr_val = 0;
   unsigned int prev_val = 0;
   unsigned int offset = 0;
   unsigned char *curr = cheat_manager_state.curr_memory_buf;
   unsigned char *prev = cheat_manager_state.prev_memory_buf;
   unsigned int curr_match_idx = 0;

   if (target_match_idx > cheat_manager_state.num_matches - 1)
      return;

   if (cheat_manager_state.num_memory_buffers == 0)
      return;

   cheat_manager_setup_search_meta(cheat_manager_state.search_bit_size, &bytes_per_item, &mask, &bits);

   if (match_action == CHEAT_MATCH_ACTION_TYPE_BROWSE)
      start_idx = *address;
   else
      start_idx = 0;

   for (idx = start_idx; idx < cheat_manager_state.total_memory_size; idx = idx + bytes_per_item)
   {
      offset = translate_address(idx, &curr);

      switch (bytes_per_item)
      {
      case 2:
         curr_val = cheat_manager_state.big_endian ?
               (*(curr + idx - offset) * 256) + *(curr + idx + 1 - offset) :
               *(curr + idx - offset) + (*(curr + idx + 1 - offset) * 256);
         if (prev)
            prev_val = cheat_manager_state.big_endian ?
                  (*(prev + idx) * 256) + *(prev + idx + 1) :
                  *(prev + idx) + (*(prev + idx + 1) * 256);
         break;
      case 4:
         curr_val = cheat_manager_state.big_endian ?
               (*(curr + idx - offset) * 256 * 256 * 256) + (*(curr + idx + 1 - offset) * 256 * 256) + (*(curr + idx + 2 - offset) * 256) + *(curr + idx + 3 - offset) :
               *(curr + idx - offset) + (*(curr + idx + 1 - offset) * 256) + (*(curr + idx + 2 - offset) * 256 * 256) + (*(curr + idx + 3 - offset) * 256 * 256 * 256);
         if (prev)
            prev_val = cheat_manager_state.big_endian ?
                  (*(prev + idx) * 256 * 256 * 256) + (*(prev + idx + 1) * 256 * 256) + (*(prev + idx + 2) * 256) + *(prev + idx + 3) :
                  *(prev + idx) + (*(prev + idx + 1) * 256) + (*(prev + idx + 2) * 256 * 256) + (*(prev + idx + 3) * 256 * 256 * 256);
         break;
      case 1:
      default:
         curr_val = *(curr + idx - offset);
         if (prev)
            prev_val = *(prev + idx);
         break;
      }

      if (match_action == CHEAT_MATCH_ACTION_TYPE_BROWSE)
      {
         *curr_value = curr_val;
         *prev_value = prev_val;
         return;
      }

      if (!prev)
         return;

      for (byte_part = 0; byte_part < 8 / bits; byte_part++)
      {
         unsigned int prev_match;

         if (bits < 8)
         {
            prev_match = *(cheat_manager_state.matches + idx) & (mask << (byte_part * bits));
            if (prev_match)
            {
               if (target_match_idx == curr_match_idx)
               {
                  switch (match_action)
                  {
                  case CHEAT_MATCH_ACTION_TYPE_BROWSE:
                     return;
                  case CHEAT_MATCH_ACTION_TYPE_VIEW:
                     *address = idx;
                     *address_mask = (mask << (byte_part * bits));
                     *curr_value = curr_val;
                     *prev_value = prev_val;
                     return;
                  case CHEAT_MATCH_ACTION_TYPE_COPY:
                     if (!cheat_manager_add_new_code(cheat_manager_state.search_bit_size, idx, (mask << (byte_part * bits)),
                           cheat_manager_state.big_endian, curr_val))
                        runloop_msg_queue_push(msg_hash_to_str(MSG_CHEAT_SEARCH_ADD_MATCH_FAIL), 1, 180, true, NULL, MESSAGE_QUEUE_ICON_DEFAULT, MESSAGE_QUEUE_CATEGORY_INFO);
                     else
                        runloop_msg_queue_push(msg_hash_to_str(MSG_CHEAT_SEARCH_ADD_MATCH_SUCCESS), 1, 180, true, NULL, MESSAGE_QUEUE_ICON_DEFAULT, MESSAGE_QUEUE_CATEGORY_INFO);
                     return;
                  case CHEAT_MATCH_ACTION_TYPE_DELETE:
                     if (bits < 8)
                        *(cheat_manager_state.matches + idx) = *(cheat_manager_state.matches + idx) &
                              ((~(mask << (byte_part * bits))) & 0xFF);
                     else
                        memset(cheat_manager_state.matches + idx, 0, bytes_per_item);
                     if (cheat_manager_state.num_matches > 0)
                        cheat_manager_state.num_matches--;
                     runloop_msg_queue_push(msg_hash_to_str(MSG_CHEAT_SEARCH_DELETE_MATCH_SUCCESS), 1, 180, true, NULL, MESSAGE_QUEUE_ICON_DEFAULT, MESSAGE_QUEUE_CATEGORY_INFO);
                     return;
                  }
                  return;
               }
               curr_match_idx++;
            }
         }
         else
         {
            prev_match = *(cheat_manager_state.matches + idx);
            if (prev_match)
            {
               if (target_match_idx == curr_match_idx)
               {
                  switch (match_action)
                  {
                  case CHEAT_MATCH_ACTION_TYPE_BROWSE:
                     return;
                  case CHEAT_MATCH_ACTION_TYPE_VIEW:
                     *address = idx;
                     *address_mask = 0xFF;
                     *curr_value = curr_val;
                     *prev_value = prev_val;
                     return;
                  case CHEAT_MATCH_ACTION_TYPE_COPY:
                     if (!cheat_manager_add_new_code(cheat_manager_state.search_bit_size, idx, 0xFF,
                           cheat_manager_state.big_endian, curr_val))
                        runloop_msg_queue_push(msg_hash_to_str(MSG_CHEAT_SEARCH_ADD_MATCH_FAIL), 1, 180, true, NULL, MESSAGE_QUEUE_ICON_DEFAULT, MESSAGE_QUEUE_CATEGORY_INFO);
                     else
                        runloop_msg_queue_push(msg_hash_to_str(MSG_CHEAT_SEARCH_ADD_MATCH_SUCCESS), 1, 180, true, NULL, MESSAGE_QUEUE_ICON_DEFAULT, MESSAGE_QUEUE_CATEGORY_INFO);
                     return;
                  case CHEAT_MATCH_ACTION_TYPE_DELETE:
                     if (bits < 8)
                        *(cheat_manager_state.matches + idx) = *(cheat_manager_state.matches + idx) &
                              ((~(mask << (byte_part * bits))) & 0xFF);
                     else
                        memset(cheat_manager_state.matches + idx, 0, bytes_per_item);
                     if (cheat_manager_state.num_matches > 0)
                        cheat_manager_state.num_matches--;
                     runloop_msg_queue_push(msg_hash_to_str(MSG_CHEAT_SEARCH_DELETE_MATCH_SUCCESS), 1, 180, true, NULL, MESSAGE_QUEUE_ICON_DEFAULT, MESSAGE_QUEUE_CATEGORY_INFO);
                     return;
                  }
               }

               curr_match_idx++;
            }
         }
      }
   }

}