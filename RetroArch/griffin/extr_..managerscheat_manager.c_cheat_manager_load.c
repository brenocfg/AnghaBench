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
typedef  int /*<<< orphan*/  config_file_t ;
struct TYPE_6__ {int /*<<< orphan*/  config_file_new_entry_cb; } ;
typedef  TYPE_2__ config_file_cb_t ;
struct TYPE_7__ {unsigned int loading_cheat_size; unsigned int loading_cheat_offset; TYPE_1__* cheats; } ;
struct TYPE_5__ {unsigned int idx; int state; int big_endian; int memory_search_size; int /*<<< orphan*/  cheat_type; int /*<<< orphan*/ * code; int /*<<< orphan*/ * desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHEAT_HANDLER_TYPE_EMU ; 
 int /*<<< orphan*/  CHEAT_TYPE_SET_TO_VALUE ; 
 int /*<<< orphan*/  cheat_manager_alloc_if_empty () ; 
 unsigned int cheat_manager_get_size () ; 
 int /*<<< orphan*/  cheat_manager_load_cb_first_pass ; 
 int /*<<< orphan*/  cheat_manager_load_cb_second_pass ; 
 int /*<<< orphan*/  cheat_manager_new (unsigned int) ; 
 scalar_t__ cheat_manager_realloc (unsigned int,int /*<<< orphan*/ ) ; 
 TYPE_4__ cheat_manager_state ; 
 int /*<<< orphan*/  config_file_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * config_file_new_with_callback (char const*,TYPE_2__*) ; 

bool cheat_manager_load(const char *path, bool append)
{
   config_file_cb_t cb;
   unsigned orig_size  = 0;
   unsigned cheats     = 0;
   unsigned i          = 0;
   config_file_t *conf = NULL;

   cb.config_file_new_entry_cb = cheat_manager_load_cb_first_pass;

   cheat_manager_state.loading_cheat_size = 0;

   conf = config_file_new_with_callback(path, &cb);

   if (!conf)
      return false;

   cheats = cheat_manager_state.loading_cheat_size;

   if (cheats == 0)
      goto error;

   config_file_free(conf);
   conf = NULL;

   cheat_manager_alloc_if_empty();

   if (append)
   {
      orig_size = cheat_manager_get_size();
      if (orig_size == 0)
         cheat_manager_new(cheats);
      else
      {
         cheats = cheats + orig_size;
         if (cheat_manager_realloc(cheats, CHEAT_HANDLER_TYPE_EMU))
         {
         }
      }
   }
   else
   {
      orig_size = 0;
      cheat_manager_new(cheats);
   }

   for (i = orig_size; cheat_manager_state.cheats && i < cheats; i++)
   {
      cheat_manager_state.cheats[i].idx = i;
      cheat_manager_state.cheats[i].desc = NULL;
      cheat_manager_state.cheats[i].code = NULL;
      cheat_manager_state.cheats[i].state = false;
      cheat_manager_state.cheats[i].big_endian = false;
      cheat_manager_state.cheats[i].cheat_type = CHEAT_TYPE_SET_TO_VALUE;
      cheat_manager_state.cheats[i].memory_search_size = 3;
   }

   cheat_manager_state.loading_cheat_offset = orig_size;
   cb.config_file_new_entry_cb = cheat_manager_load_cb_second_pass;
   conf = config_file_new_with_callback(path, &cb);

   if (!conf)
      return false;

   config_file_free(conf);

   return true;

error:
   config_file_free(conf);
   return false;
}