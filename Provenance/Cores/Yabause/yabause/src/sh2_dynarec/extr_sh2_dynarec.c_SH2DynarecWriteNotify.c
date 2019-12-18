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
 int* cached_code ; 
 int /*<<< orphan*/  invalidate_blocks (int,int) ; 

void SH2DynarecWriteNotify(u32 start, u32 length) {
  int block,wp=0;
  // Ignore non-RAM regions
  if((start&0xDFF00000)!=0x200000&&(start&0xDE000000)!=0x6000000) return;
  // Check if any pages contain compiled code
  for(block=start>>12;block<=(start+length-1)>>12;block++)
    wp|=((cached_code[block>>3]>>(block&7))&1);
  if(!wp) return;
  //printf("SH2DynarecWriteNotify(%x,%x)\n",start,length);
  invalidate_blocks(start>>12,(start+length-1)>>12);
}