#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ram_type {int /*<<< orphan*/  path; int /*<<< orphan*/  type; } ;
struct TYPE_3__ {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ retro_ctx_memory_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_FAILED_TO_SAVE_SRAM ; 
 int /*<<< orphan*/  MSG_SAVED_SUCCESSFULLY_TO ; 
 int /*<<< orphan*/  MSG_SAVING_RAM_TYPE ; 
 int /*<<< orphan*/  MSG_TO ; 
 int /*<<< orphan*/  RARCH_ERR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RARCH_LOG (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  RARCH_WARN (char*) ; 
 int /*<<< orphan*/  content_get_memory (TYPE_1__*,struct ram_type*,unsigned int) ; 
 int /*<<< orphan*/  dump_to_file_desperate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  filestream_write_file (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_hash_to_str (int /*<<< orphan*/ ) ; 

bool content_save_ram_file(unsigned slot)
{
   struct ram_type ram;
   retro_ctx_memory_info_t mem_info;

   if (!content_get_memory(&mem_info, &ram, slot))
      return false;

   RARCH_LOG("%s #%u %s \"%s\".\n",
         msg_hash_to_str(MSG_SAVING_RAM_TYPE),
         ram.type,
         msg_hash_to_str(MSG_TO),
         ram.path);

   if (!filestream_write_file(
            ram.path, mem_info.data, mem_info.size))
   {
      RARCH_ERR("%s.\n",
            msg_hash_to_str(MSG_FAILED_TO_SAVE_SRAM));
      RARCH_WARN("Attempting to recover ...\n");

      /* In case the file could not be written to,
       * the fallback function 'dump_to_file_desperate'
       * will be called. */
      if (!dump_to_file_desperate(
               mem_info.data, mem_info.size, ram.type))
      {
         RARCH_WARN("Failed ... Cannot recover save file.\n");
      }
      return false;
   }

   RARCH_LOG("%s \"%s\".\n",
         msg_hash_to_str(MSG_SAVED_SUCCESSFULLY_TO),
         ram.path);

   return true;
}