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
struct TYPE_2__ {int jb_pc_offset; } ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  SP_REGNUM ; 
 int TYPE_LENGTH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  builtin_type_void_data_ptr ; 
 int /*<<< orphan*/  builtin_type_void_func_ptr ; 
 int /*<<< orphan*/  current_gdbarch ; 
 int /*<<< orphan*/  current_regcache ; 
 scalar_t__ extract_typed_address (char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* gdbarch_tdep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regcache_cooked_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ target_read_memory (scalar_t__,char*,int) ; 

__attribute__((used)) static int
i386_get_longjmp_target (CORE_ADDR *pc)
{
  char buf[8];
  CORE_ADDR sp, jb_addr;
  int jb_pc_offset = gdbarch_tdep (current_gdbarch)->jb_pc_offset;
  int len = TYPE_LENGTH (builtin_type_void_func_ptr);

  /* If JB_PC_OFFSET is -1, we have no way to find out where the
     longjmp will land.  */
  if (jb_pc_offset == -1)
    return 0;

  /* Don't use I386_ESP_REGNUM here, since this function is also used
     for AMD64.  */
  regcache_cooked_read (current_regcache, SP_REGNUM, buf);
  sp = extract_typed_address (buf, builtin_type_void_data_ptr);
  if (target_read_memory (sp + len, buf, len))
    return 0;

  jb_addr = extract_typed_address (buf, builtin_type_void_data_ptr);
  if (target_read_memory (jb_addr + jb_pc_offset, buf, len))
    return 0;

  *pc = extract_typed_address (buf, builtin_type_void_func_ptr);
  return 1;
}