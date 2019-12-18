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
typedef  int u32 ;
struct ll_entry {struct ll_entry* next; int /*<<< orphan*/  vaddr; scalar_t__ addr; } ;

/* Variables and functions */
 char* MAX_OUTPUT_BLOCK_SIZE ; 
 int /*<<< orphan*/  free (struct ll_entry*) ; 
 int /*<<< orphan*/  inv_debug (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_hash (int /*<<< orphan*/ ) ; 

void ll_remove_matching_addrs(struct ll_entry **head,int addr,int shift)
{
  struct ll_entry *next;
  while(*head) {
    if(((u32)((*head)->addr)>>shift)==(addr>>shift) || 
       ((u32)(((char *)(*head)->addr)-MAX_OUTPUT_BLOCK_SIZE)>>shift)==(addr>>shift))
    {
      inv_debug("EXP: Remove pointer to %x (%x)\n",(int)(*head)->addr,(*head)->vaddr);
      remove_hash((*head)->vaddr);
      next=(*head)->next;
      free(*head);
      *head=next;
    }
    else
    {
      head=&((*head)->next);
    }
  }
}