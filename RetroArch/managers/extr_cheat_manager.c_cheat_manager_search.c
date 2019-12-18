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
typedef  int /*<<< orphan*/  msg ;
typedef  enum cheat_search_type { ____Placeholder_cheat_search_type } cheat_search_type ;
struct TYPE_2__ {unsigned char* curr_memory_buf; unsigned char* prev_memory_buf; unsigned int num_memory_buffers; unsigned int total_memory_size; unsigned int* matches; unsigned int search_exact_value; scalar_t__ num_matches; scalar_t__* memory_size_list; int /*<<< orphan*/ * memory_buf_list; int /*<<< orphan*/  search_eqminus_value; int /*<<< orphan*/  search_eqplus_value; int /*<<< orphan*/  big_endian; int /*<<< orphan*/  search_bit_size; } ;

/* Variables and functions */
#define  CHEAT_SEARCH_TYPE_EQ 136 
#define  CHEAT_SEARCH_TYPE_EQMINUS 135 
#define  CHEAT_SEARCH_TYPE_EQPLUS 134 
#define  CHEAT_SEARCH_TYPE_EXACT 133 
#define  CHEAT_SEARCH_TYPE_GT 132 
#define  CHEAT_SEARCH_TYPE_GTE 131 
#define  CHEAT_SEARCH_TYPE_LT 130 
#define  CHEAT_SEARCH_TYPE_LTE 129 
#define  CHEAT_SEARCH_TYPE_NEQ 128 
 int /*<<< orphan*/  MENU_ENTRIES_CTL_SET_REFRESH ; 
 int /*<<< orphan*/  MESSAGE_QUEUE_CATEGORY_INFO ; 
 int /*<<< orphan*/  MESSAGE_QUEUE_ICON_DEFAULT ; 
 int /*<<< orphan*/  MSG_CHEAT_SEARCH_FOUND_MATCHES ; 
 int /*<<< orphan*/  MSG_CHEAT_SEARCH_NOT_INITIALIZED ; 
 int /*<<< orphan*/  RARCH_MENU_CTL_SET_PREVENT_POPULATE ; 
 int /*<<< orphan*/  cheat_manager_setup_search_meta (int /*<<< orphan*/ ,unsigned int*,unsigned int*,unsigned int*) ; 
 TYPE_1__ cheat_manager_state ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  memset (unsigned int*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  menu_driver_ctl (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  menu_entries_ctl (int /*<<< orphan*/ ,int*) ; 
 char* msg_hash_to_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  runloop_msg_queue_push (char*,int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,scalar_t__) ; 
 unsigned int translate_address (unsigned int,unsigned char**) ; 

__attribute__((used)) static int cheat_manager_search(enum cheat_search_type search_type)
{
   char msg[100];
   unsigned char *curr         = cheat_manager_state.curr_memory_buf;
   unsigned char *prev         = cheat_manager_state.prev_memory_buf;
   unsigned int idx            = 0;
   unsigned int curr_val       = 0;
   unsigned int prev_val       = 0;
   unsigned int mask           = 0;
   unsigned int bytes_per_item = 1;
   unsigned int bits           = 8;
   unsigned int offset         = 0;
   unsigned int i              = 0;
   bool refresh                = false;

   if (cheat_manager_state.num_memory_buffers == 0)
   {
      runloop_msg_queue_push(msg_hash_to_str(MSG_CHEAT_SEARCH_NOT_INITIALIZED), 1, 180, true, NULL, MESSAGE_QUEUE_ICON_DEFAULT, MESSAGE_QUEUE_CATEGORY_INFO);
      return 0;
   }

   cheat_manager_setup_search_meta(cheat_manager_state.search_bit_size, &bytes_per_item, &mask, &bits);

   /* little endian FF000000 = 256 */
   for (idx = 0; idx < cheat_manager_state.total_memory_size; idx = idx + bytes_per_item)
   {
      unsigned byte_part;

      offset = translate_address(idx, &curr);

      switch (bytes_per_item)
      {
         case 2:
            curr_val = cheat_manager_state.big_endian ?
               (*(curr + idx - offset) * 256) + *(curr + idx + 1 - offset) :
               *(curr + idx - offset) + (*(curr + idx + 1 - offset) * 256);
            prev_val = cheat_manager_state.big_endian ?
               (*(prev + idx) * 256) + *(prev + idx + 1) :
               *(prev + idx) + (*(prev + idx + 1) * 256);
            break;
         case 4:
            curr_val = cheat_manager_state.big_endian ?
               (*(curr + idx - offset) * 256 * 256 * 256) + (*(curr + idx + 1 - offset) * 256 * 256) + (*(curr + idx + 2 - offset) * 256) + *(curr + idx + 3 - offset) :
               *(curr + idx - offset) + (*(curr + idx + 1 - offset) * 256) + (*(curr + idx + 2 - offset) * 256 * 256) + (*(curr + idx + 3 - offset) * 256 * 256 * 256);
            prev_val = cheat_manager_state.big_endian ?
               (*(prev + idx) * 256 * 256 * 256) + (*(prev + idx + 1) * 256 * 256) + (*(prev + idx + 2) * 256) + *(prev + idx + 3) :
               *(prev + idx) + (*(prev + idx + 1) * 256) + (*(prev + idx + 2) * 256 * 256) + (*(prev + idx + 3) * 256 * 256 * 256);
            break;
         case 1:
         default:
            curr_val = *(curr - offset + idx);
            prev_val = *(prev + idx);
            break;
      }

      for (byte_part = 0; byte_part < 8 / bits; byte_part++)
      {
         unsigned int curr_subval = (curr_val >> (byte_part * bits)) & mask;
         unsigned int prev_subval = (prev_val >> (byte_part * bits)) & mask;
         unsigned int prev_match;

         if (bits < 8)
            prev_match = *(cheat_manager_state.matches + idx) & (mask << (byte_part * bits));
         else
            prev_match = *(cheat_manager_state.matches + idx);

         if (prev_match > 0)
         {
            bool match = false;
            switch (search_type)
            {
               case CHEAT_SEARCH_TYPE_EXACT:
                  match = (curr_subval == cheat_manager_state.search_exact_value);
                  break;
               case CHEAT_SEARCH_TYPE_LT:
                  match = (curr_subval < prev_subval);
                  break;
               case CHEAT_SEARCH_TYPE_GT:
                  match = (curr_subval > prev_subval);
                  break;
               case CHEAT_SEARCH_TYPE_LTE:
                  match = (curr_subval <= prev_subval);
                  break;
               case CHEAT_SEARCH_TYPE_GTE:
                  match = (curr_subval >= prev_subval);
                  break;
               case CHEAT_SEARCH_TYPE_EQ:
                  match = (curr_subval == prev_subval);
                  break;
               case CHEAT_SEARCH_TYPE_NEQ:
                  match = (curr_subval != prev_subval);
                  break;
               case CHEAT_SEARCH_TYPE_EQPLUS:
                  match = (curr_subval == prev_subval + cheat_manager_state.search_eqplus_value);
                  break;
               case CHEAT_SEARCH_TYPE_EQMINUS:
                  match = (curr_subval == prev_subval - cheat_manager_state.search_eqminus_value);
                  break;
            }

            if (!match)
            {
               if (bits < 8)
                  *(cheat_manager_state.matches + idx) = *(cheat_manager_state.matches + idx) &
                     ((~(mask << (byte_part * bits))) & 0xFF);
               else
                  memset(cheat_manager_state.matches + idx, 0, bytes_per_item);
               if (cheat_manager_state.num_matches > 0)
                  cheat_manager_state.num_matches--;
            }
         }
      }
   }

   offset = 0;

   for (i = 0; i < cheat_manager_state.num_memory_buffers; i++)
   {
      memcpy(cheat_manager_state.prev_memory_buf + offset, cheat_manager_state.memory_buf_list[i], cheat_manager_state.memory_size_list[i]);
      offset += cheat_manager_state.memory_size_list[i];
   }

   snprintf(msg, sizeof(msg), msg_hash_to_str(MSG_CHEAT_SEARCH_FOUND_MATCHES), cheat_manager_state.num_matches);
   msg[sizeof(msg) - 1] = 0;

   runloop_msg_queue_push(msg, 1, 180, true, NULL, MESSAGE_QUEUE_ICON_DEFAULT, MESSAGE_QUEUE_CATEGORY_INFO);

#ifdef HAVE_MENU
   menu_entries_ctl(MENU_ENTRIES_CTL_SET_REFRESH, &refresh);
   menu_driver_ctl(RARCH_MENU_CTL_SET_PREVENT_POPULATE, NULL);
#endif
   return 0;
}