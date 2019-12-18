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
struct ll_entry {int vaddr; void* addr; struct ll_entry* next; } ;

/* Variables and functions */
 int MAX_OUTPUT_BLOCK_SIZE ; 
 int TARGET_SIZE_2 ; 
 int** hash_table ; 
 scalar_t__ isclean (int) ; 
 struct ll_entry** jump_in ; 
 scalar_t__ out ; 

void *check_addr(u32 vaddr)
{
  struct ll_entry *head;
  u32 page;
  u32 *ht_bin=hash_table[((vaddr>>16)^vaddr)&0xFFFF];
  if(ht_bin[0]==vaddr) {
    if(((ht_bin[1]-MAX_OUTPUT_BLOCK_SIZE-(u32)out)<<(32-TARGET_SIZE_2))>0x60000000+(MAX_OUTPUT_BLOCK_SIZE<<(32-TARGET_SIZE_2)))
      if(isclean(ht_bin[1])) return (void *)ht_bin[1];
  }
  if(ht_bin[2]==vaddr) {
    if(((ht_bin[3]-MAX_OUTPUT_BLOCK_SIZE-(u32)out)<<(32-TARGET_SIZE_2))>0x60000000+(MAX_OUTPUT_BLOCK_SIZE<<(32-TARGET_SIZE_2)))
      if(isclean(ht_bin[3])) return (void *)ht_bin[3];
  }
  page=(vaddr&0xDFFFFFFF)>>12;
  if(page>1024) page=1024+(page&1023);
  head=jump_in[page];
  while(head!=NULL) {
    if(head->vaddr==vaddr) {
      if((((u32)head->addr-(u32)out)<<(32-TARGET_SIZE_2))>0x60000000+(MAX_OUTPUT_BLOCK_SIZE<<(32-TARGET_SIZE_2))) {
        // Update existing entry with current address
        if(ht_bin[0]==vaddr) {
          ht_bin[1]=(int)head->addr;
          return head->addr;
        }
        if(ht_bin[2]==vaddr) {
          ht_bin[3]=(int)head->addr;
          return head->addr;
        }
        // Insert into hash table with low priority.
        // Don't evict existing entries, as they are probably
        // addresses that are being accessed frequently.
        if(ht_bin[0]==-1) {
          ht_bin[1]=(int)head->addr;
          ht_bin[0]=vaddr;
        }else if(ht_bin[2]==-1) {
          ht_bin[3]=(int)head->addr;
          ht_bin[2]=vaddr;
        }
        return head->addr;
      }
    }
    head=head->next;
  }
  return 0;
}