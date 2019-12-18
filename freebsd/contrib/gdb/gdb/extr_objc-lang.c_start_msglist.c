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
struct selname {char* msglist_sel; scalar_t__ msglist_len; struct selname* next; } ;

/* Variables and functions */
 scalar_t__ msglist_len ; 
 char* msglist_sel ; 
 struct selname* selname_chain ; 
 scalar_t__ xmalloc (int) ; 

void
start_msglist(void)
{
  struct selname *new = 
    (struct selname *) xmalloc (sizeof (struct selname));

  new->next = selname_chain;
  new->msglist_len = msglist_len;
  new->msglist_sel = msglist_sel;
  msglist_len = 0;
  msglist_sel = (char *)xmalloc(1);
  *msglist_sel = 0;
  selname_chain = new;
}