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

/* Variables and functions */
 int** hash_table ; 

void remove_hash(int vaddr)
{
  //printf("remove hash: %x\n",vaddr);
  int *ht_bin=hash_table[(((vaddr)>>16)^vaddr)&0xFFFF];
  if(ht_bin[2]==vaddr) {
    ht_bin[2]=ht_bin[3]=-1;
  }
  if(ht_bin[0]==vaddr) {
    ht_bin[0]=ht_bin[2];
    ht_bin[1]=ht_bin[3];
    ht_bin[2]=ht_bin[3]=-1;
  }
}