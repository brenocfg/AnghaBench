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
struct function_info {struct call_info* call_list; } ;
struct call_info {scalar_t__ fun; scalar_t__ is_tail; struct call_info* next; } ;
typedef  int /*<<< orphan*/  bfd_boolean ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static bfd_boolean
insert_callee (struct function_info *caller, struct call_info *callee)
{
  struct call_info *p;
  for (p = caller->call_list; p != NULL; p = p->next)
    if (p->fun == callee->fun)
      {
	/* Tail calls use less stack than normal calls.  Retain entry
	   for normal call over one for tail call.  */
	if (p->is_tail > callee->is_tail)
	  p->is_tail = callee->is_tail;
	return FALSE;
      }
  callee->next = caller->call_list;
  caller->call_list = callee;
  return TRUE;
}