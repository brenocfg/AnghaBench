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
struct ll_entry {struct ll_entry* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct ll_entry*) ; 

void ll_clear(struct ll_entry **head)
{
  struct ll_entry *cur;
  struct ll_entry *next;
  if(cur=*head) {
    *head=0;
    while(cur) {
      next=cur->next;
      free(cur);
      cur=next;
    }
  }
}