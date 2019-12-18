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
struct TYPE_3__ {int endbit; int endbyte; int storage; long* ptr; } ;
typedef  TYPE_1__ oggpack_buffer ;

/* Variables and functions */
 unsigned long* mask ; 

long oggpack_read(oggpack_buffer *b,int bits){
  long ret;
  unsigned long m;

  if(bits<0 || bits>32) goto err;
  m=mask[bits];
  bits+=b->endbit;

  if(b->endbyte >= b->storage-4){
    /* not the main path */
    if(b->endbyte > b->storage-((bits+7)>>3)) goto overflow;
    /* special case to avoid reading b->ptr[0], which might be past the end of
        the buffer; also skips some useless accounting */
    else if(!bits)return(0L);
  }

  ret=b->ptr[0]>>b->endbit;
  if(bits>8){
    ret|=b->ptr[1]<<(8-b->endbit);
    if(bits>16){
      ret|=b->ptr[2]<<(16-b->endbit);
      if(bits>24){
        ret|=b->ptr[3]<<(24-b->endbit);
        if(bits>32 && b->endbit){
          ret|=b->ptr[4]<<(32-b->endbit);
        }
      }
    }
  }
  ret&=m;
  b->ptr+=bits/8;
  b->endbyte+=bits/8;
  b->endbit=bits&7;
  return ret;

 overflow:
 err:
  b->ptr=NULL;
  b->endbyte=b->storage;
  b->endbit=1;
  return -1L;
}