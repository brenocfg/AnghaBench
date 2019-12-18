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
struct TYPE_2__ {unsigned char* curr_memory_buf; int num_matches; int size; unsigned int total_memory_size; unsigned int* matches; int /*<<< orphan*/  big_endian; int /*<<< orphan*/  search_bit_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  MENU_ENTRIES_CTL_SET_REFRESH ; 
 int /*<<< orphan*/  MESSAGE_QUEUE_CATEGORY_INFO ; 
 int /*<<< orphan*/  MESSAGE_QUEUE_ICON_DEFAULT ; 
 int /*<<< orphan*/  MSG_CHEAT_SEARCH_ADDED_MATCHES_FAIL ; 
 int /*<<< orphan*/  MSG_CHEAT_SEARCH_ADDED_MATCHES_SUCCESS ; 
 int /*<<< orphan*/  MSG_CHEAT_SEARCH_ADDED_MATCHES_TOO_MANY ; 
 int /*<<< orphan*/  RARCH_MENU_CTL_SET_PREVENT_POPULATE ; 
 int /*<<< orphan*/  cheat_manager_add_new_code (int /*<<< orphan*/ ,unsigned int,int,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  cheat_manager_setup_search_meta (int /*<<< orphan*/ ,unsigned int*,unsigned int*,unsigned int*) ; 
 TYPE_1__ cheat_manager_state ; 
 int /*<<< orphan*/  menu_driver_ctl (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  menu_entries_ctl (int /*<<< orphan*/ ,int*) ; 
 char* msg_hash_to_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  runloop_msg_queue_push (char*,int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 unsigned int translate_address (unsigned int,unsigned char**) ; 

int cheat_manager_add_matches(const char *path,
      const char *label, unsigned type, size_t menuidx, size_t entry_idx)
{
   char msg[100];
   bool refresh = false;
   unsigned byte_part = 0;
   unsigned int idx = 0;
   unsigned int mask = 0;
   unsigned int bytes_per_item = 1;
   unsigned int bits = 8;
   unsigned int curr_val = 0;
   unsigned int num_added = 0;
   unsigned int offset = 0;
   unsigned char *curr = cheat_manager_state.curr_memory_buf;

   if (cheat_manager_state.num_matches + cheat_manager_state.size > 100)
   {
      runloop_msg_queue_push(msg_hash_to_str(MSG_CHEAT_SEARCH_ADDED_MATCHES_TOO_MANY), 1, 180, true, NULL, MESSAGE_QUEUE_ICON_DEFAULT, MESSAGE_QUEUE_CATEGORY_INFO);
      return 0;
   }
   cheat_manager_setup_search_meta(cheat_manager_state.search_bit_size, &bytes_per_item, &mask, &bits);

   for (idx = 0; idx < cheat_manager_state.total_memory_size; idx = idx + bytes_per_item)
   {
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
         curr_val = *(curr - offset + idx);
         break;
      }
      for (byte_part = 0; byte_part < 8 / bits; byte_part++)
      {
         unsigned int prev_match;

         if (bits < 8)
         {
            prev_match = *(cheat_manager_state.matches + idx) & (mask << (byte_part * bits));
            if (prev_match)
            {
               if (!cheat_manager_add_new_code(cheat_manager_state.search_bit_size, idx, (mask << (byte_part * bits)),
                     cheat_manager_state.big_endian, curr_val))
               {
                  runloop_msg_queue_push(msg_hash_to_str(MSG_CHEAT_SEARCH_ADDED_MATCHES_FAIL), 1, 180, true, NULL, MESSAGE_QUEUE_ICON_DEFAULT, MESSAGE_QUEUE_CATEGORY_INFO);
                  return 0;
               }
               num_added++;
            }
         }
         else
         {
            prev_match = *(cheat_manager_state.matches + idx);
            if (prev_match)
            {
               if (!cheat_manager_add_new_code(cheat_manager_state.search_bit_size, idx, 0xFF,
                     cheat_manager_state.big_endian, curr_val))
               {
                  runloop_msg_queue_push(msg_hash_to_str(MSG_CHEAT_SEARCH_ADDED_MATCHES_FAIL), 1, 180, true, NULL, MESSAGE_QUEUE_ICON_DEFAULT, MESSAGE_QUEUE_CATEGORY_INFO);
                  return 0;
               }
               num_added++;
            }
         }

      }
   }

   snprintf(msg, sizeof(msg), msg_hash_to_str(MSG_CHEAT_SEARCH_ADDED_MATCHES_SUCCESS), cheat_manager_state.num_matches);
   msg[sizeof(msg) - 1] = 0;

   runloop_msg_queue_push(msg, 1, 180, true, NULL, MESSAGE_QUEUE_ICON_DEFAULT, MESSAGE_QUEUE_CATEGORY_INFO);

#ifdef HAVE_MENU
   menu_entries_ctl(MENU_ENTRIES_CTL_SET_REFRESH, &refresh);
   menu_driver_ctl(RARCH_MENU_CTL_SET_PREVENT_POPULATE, NULL);
#endif

   return 0;
}