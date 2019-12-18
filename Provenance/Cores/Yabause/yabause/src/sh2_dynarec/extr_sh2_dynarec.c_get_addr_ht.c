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
 void* get_addr (int) ; 
 int** hash_table ; 

void *get_addr_ht(u32 vaddr)
{
  //printf("TRACE: count=%d next=%d (get_addr_ht %x)\n",Count,next_interupt,vaddr);
  //if(vaddr>>12==0x60a0) printf("TRACE: (get_addr_ht %x)\n",vaddr);
  int *ht_bin=hash_table[((vaddr>>16)^vaddr)&0xFFFF];
  //if(vaddr>>12==0x60a0) printf("%x %x %x %x\n",ht_bin[0],ht_bin[1],ht_bin[2],ht_bin[3]);
  if(ht_bin[0]==vaddr) return (void *)ht_bin[1];
  if(ht_bin[2]==vaddr) return (void *)ht_bin[3];
  return get_addr(vaddr);
}