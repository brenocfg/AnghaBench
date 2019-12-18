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
typedef  size_t u32 ;
struct ll_entry {struct ll_entry* next; scalar_t__ addr; int /*<<< orphan*/  vaddr; } ;

/* Variables and functions */
 scalar_t__ BASE_ADDR ; 
 int /*<<< orphan*/  free (struct ll_entry*) ; 
 int /*<<< orphan*/  inv_debug (char*,int /*<<< orphan*/ ,...) ; 
 struct ll_entry** jump_in ; 
 struct ll_entry** jump_out ; 
 scalar_t__ kill_pointer (scalar_t__) ; 
 int* needs_clear_cache ; 
 int /*<<< orphan*/  remove_hash (int /*<<< orphan*/ ) ; 

void invalidate_page(u32 page)
{
  struct ll_entry *head;
  struct ll_entry *next;
  head=jump_in[page];
  jump_in[page]=0;
  while(head!=NULL) {
    inv_debug("INVALIDATE: %x\n",head->vaddr);
    remove_hash(head->vaddr);
    next=head->next;
    free(head);
    head=next;
  }
  head=jump_out[page];
  jump_out[page]=0;
  while(head!=NULL) {
    u32 host_addr;
    inv_debug("INVALIDATE: kill pointer to %x (%x)\n",head->vaddr,(int)head->addr);
    host_addr=(u32)kill_pointer(head->addr);
    #ifdef __arm__
      needs_clear_cache[(host_addr-(u32)BASE_ADDR)>>17]|=1<<(((host_addr-(u32)BASE_ADDR)>>12)&31);
    #endif
    next=head->next;
    free(head);
    head=next;
  }
}