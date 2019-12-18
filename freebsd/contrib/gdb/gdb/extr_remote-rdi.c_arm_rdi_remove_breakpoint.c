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
struct local_bp_list_entry {scalar_t__ addr; struct local_bp_list_entry* next; int /*<<< orphan*/  point; } ;
typedef  int /*<<< orphan*/  PointHandle ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 int RDIError_NoError ; 
 int angel_RDI_clearbreak (int /*<<< orphan*/ ) ; 
 struct local_bp_list_entry* local_bp_list ; 
 int /*<<< orphan*/  printf_filtered (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdi_error_message (int) ; 
 int /*<<< orphan*/  xfree (struct local_bp_list_entry*) ; 

__attribute__((used)) static int
arm_rdi_remove_breakpoint (CORE_ADDR addr, char *contents_cache)
{
  int rslt;
  PointHandle point;
  struct local_bp_list_entry **entryp, *dead;

  for (entryp = &local_bp_list; *entryp != NULL; entryp = &(*entryp)->next)
    if ((*entryp)->addr == addr)
      break;

  if (*entryp)
    {
      dead = *entryp;
      rslt = angel_RDI_clearbreak (dead->point);
      if (rslt != RDIError_NoError)
	printf_filtered ("RDI_clearbreak: %s\n", rdi_error_message (rslt));

      /* Delete the breakpoint entry locally.  */
      *entryp = dead->next;
      xfree (dead);
    }

  return 0;
}