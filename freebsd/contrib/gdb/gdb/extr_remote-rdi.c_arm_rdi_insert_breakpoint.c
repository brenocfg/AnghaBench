#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct local_bp_list_entry {struct local_bp_list_entry* next; int /*<<< orphan*/  point; int /*<<< orphan*/  addr; } ;
typedef  int /*<<< orphan*/  PointHandle ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int RDIError_NoError ; 
 int RDIPoint_16Bit ; 
 int RDIPoint_EQ ; 
 int angel_RDI_setbreak (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ arm_pc_is_thumb (int /*<<< orphan*/ ) ; 
 scalar_t__ arm_pc_is_thumb_dummy (int /*<<< orphan*/ ) ; 
 struct local_bp_list_entry* local_bp_list ; 
 int /*<<< orphan*/  printf_filtered (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdi_error_message (int) ; 
 scalar_t__ xmalloc (int) ; 

__attribute__((used)) static int
arm_rdi_insert_breakpoint (CORE_ADDR addr, char *contents_cache)
{
  int rslt;
  PointHandle point;
  struct local_bp_list_entry *entry;
  int type = RDIPoint_EQ;

  if (arm_pc_is_thumb (addr) || arm_pc_is_thumb_dummy (addr))
    type |= RDIPoint_16Bit;
  rslt = angel_RDI_setbreak (addr, type, 0, &point);
  if (rslt != RDIError_NoError)
    {
      printf_filtered ("RDI_setbreak: %s\n", rdi_error_message (rslt));
    }
  entry =
    (struct local_bp_list_entry *) xmalloc (sizeof (struct local_bp_list_entry));
  entry->addr = addr;
  entry->point = point;
  entry->next = local_bp_list;
  local_bp_list = entry;
  return rslt;
}