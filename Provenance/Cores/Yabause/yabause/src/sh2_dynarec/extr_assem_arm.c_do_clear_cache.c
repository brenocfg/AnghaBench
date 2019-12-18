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
 int BASE_ADDR ; 
 int TARGET_SIZE_2 ; 
 int /*<<< orphan*/  __clear_cache (void*,void*) ; 
 int* needs_clear_cache ; 

void do_clear_cache()
{
  int i,j;
  for (i=0;i<(1<<(TARGET_SIZE_2-17));i++)
  {
    u32 bitmap=needs_clear_cache[i];
    if(bitmap) {
      u32 start,end;
      for(j=0;j<32;j++) 
      {
        if(bitmap&(1<<j)) {
          start=BASE_ADDR+i*131072+j*4096;
          end=start+4095;
          j++;
          while(j<32) {
            if(bitmap&(1<<j)) {
              end+=4096;
              j++;
            }else{
              __clear_cache((void *)start,(void *)end);
              break;
            }
          }
        }
      }
      needs_clear_cache[i]=0;
    }
  }
}