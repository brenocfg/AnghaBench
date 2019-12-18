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
struct ram_type {int /*<<< orphan*/  path; } ;
typedef  scalar_t__ ssize_t ;
struct TYPE_3__ {scalar_t__ size; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ retro_ctx_memory_info_t ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_BYTES ; 
 int /*<<< orphan*/  MSG_TO ; 
 int /*<<< orphan*/  RARCH_WARN (char*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  content_get_memory (TYPE_1__*,struct ram_type*,unsigned int) ; 
 int /*<<< orphan*/  filestream_read_file (int /*<<< orphan*/ ,void**,scalar_t__*) ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void*,size_t) ; 
 int /*<<< orphan*/  msg_hash_to_str (int /*<<< orphan*/ ) ; 

bool content_load_ram_file(unsigned slot)
{
   int64_t rc;
   struct ram_type ram;
   retro_ctx_memory_info_t mem_info;
   void *buf        = NULL;

   if (!content_get_memory(&mem_info, &ram, slot))
      return false;

   if (!filestream_read_file(ram.path, &buf, &rc))
      return false;

   if (rc > 0)
   {
      if (rc > (ssize_t)mem_info.size)
      {
         RARCH_WARN("SRAM is larger than implementation expects, "
               "doing partial load (truncating %u %s %s %u).\n",
               (unsigned)rc,
               msg_hash_to_str(MSG_BYTES),
               msg_hash_to_str(MSG_TO),
               (unsigned)mem_info.size);
         rc = mem_info.size;
      }
      memcpy(mem_info.data, buf, (size_t)rc);
   }

   if (buf)
      free(buf);

   return true;
}