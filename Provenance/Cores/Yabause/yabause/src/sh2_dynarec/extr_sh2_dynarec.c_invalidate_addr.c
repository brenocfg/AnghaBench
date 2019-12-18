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

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int* cached_code_words ; 
 int /*<<< orphan*/  invalidate_blocks (int,int) ; 
 int /*<<< orphan*/  invalidate_count ; 
 size_t recent_write_index ; 
 int* recent_writes ; 
 int* restore_candidate ; 

void invalidate_addr(u32 addr)
{
  u32 index=addr&0xDFFFFFFF;
  if(index>4194304) index=(addr|0x400000)&0x7fffff;
  if(!((cached_code_words[index>>5]>>((index>>2)&7))&1)) {
    // If we get an excessive number of these,
    // then we probably do want to invalidate the page
    if(invalidate_count++<500) {
      if((restore_candidate[index>>15]>>((index>>12)&7))&1) {
        recent_writes[recent_write_index]=addr;
        recent_write_index=(recent_write_index+1)&7;
      }
      return;
    }
  }
  //printf("invalidate_count: %d\n",invalidate_count);
  //printf("invalidate_addr(%x)\n",addr);
  //invalidate_block(addr>>12);
  invalidate_blocks(addr>>12,addr>>12);
  assert(!((cached_code_words[index>>5]>>((index>>2)&7))&1));
  
  // Keep track of recent writes that invalidated the cache, so we don't
  // attempt constant propagation in areas that are frequently written
  recent_writes[recent_write_index]=addr;
  recent_write_index=(recent_write_index+1)&7;
}