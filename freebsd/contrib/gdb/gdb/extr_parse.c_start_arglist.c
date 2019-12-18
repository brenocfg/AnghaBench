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
struct funcall {scalar_t__ arglist_len; struct funcall* next; } ;

/* Variables and functions */
 scalar_t__ arglist_len ; 
 struct funcall* funcall_chain ; 
 scalar_t__ xmalloc (int) ; 

void
start_arglist (void)
{
  struct funcall *new;

  new = (struct funcall *) xmalloc (sizeof (struct funcall));
  new->next = funcall_chain;
  new->arglist_len = arglist_len;
  arglist_len = 0;
  funcall_chain = new;
}