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
struct funcall {int arglist_len; struct funcall* next; } ;

/* Variables and functions */
 int arglist_len ; 
 struct funcall* funcall_chain ; 
 int /*<<< orphan*/  xfree (struct funcall*) ; 

int
end_arglist (void)
{
  int val = arglist_len;
  struct funcall *call = funcall_chain;
  funcall_chain = call->next;
  arglist_len = call->arglist_len;
  xfree (call);
  return val;
}