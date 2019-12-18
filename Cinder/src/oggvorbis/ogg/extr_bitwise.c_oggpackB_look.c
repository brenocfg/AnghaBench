#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int endbit; int endbyte; int storage; int* ptr; } ;
typedef  TYPE_1__ oggpack_buffer ;

/* Variables and functions */

long oggpackB_look(oggpack_buffer *b,int bits){
  unsigned long ret;
  int m=32-bits;

  if(m<0 || m>32) return -1;
  bits+=b->endbit;

  if(b->endbyte >= b->storage-4){
    /* not the main path */
    if(b->endbyte > b->storage-((bits+7)>>3)) return -1;
    /* special case to avoid reading b->ptr[0], which might be past the end of
        the buffer; also skips some useless accounting */
    else if(!bits)return(0L);
  }

  ret=b->ptr[0]<<(24+b->endbit);
  if(bits>8){
    ret|=b->ptr[1]<<(16+b->endbit);
    if(bits>16){
      ret|=b->ptr[2]<<(8+b->endbit);
      if(bits>24){
        ret|=b->ptr[3]<<(b->endbit);
        if(bits>32 && b->endbit)
          ret|=b->ptr[4]>>(8-b->endbit);
      }
    }
  }
  return ((ret&0xffffffff)>>(m>>1))>>((m+1)>>1);
}