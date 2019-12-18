#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int endbyte; int storage; unsigned long* ptr; unsigned long* buffer; int endbit; } ;
typedef  TYPE_1__ oggpack_buffer ;

/* Variables and functions */
 int BUFFER_INCREMENT ; 
 int LONG_MAX ; 
 void* _ogg_realloc (unsigned long*,int) ; 
 unsigned long* mask ; 
 int /*<<< orphan*/  oggpack_writeclear (TYPE_1__*) ; 

void oggpackB_write(oggpack_buffer *b,unsigned long value,int bits){
  if(bits<0 || bits>32) goto err;
  if(b->endbyte>=b->storage-4){
    void *ret;
    if(!b->ptr)return;
    if(b->storage>LONG_MAX-BUFFER_INCREMENT) goto err;
    ret=_ogg_realloc(b->buffer,b->storage+BUFFER_INCREMENT);
    if(!ret) goto err;
    b->buffer=ret;
    b->storage+=BUFFER_INCREMENT;
    b->ptr=b->buffer+b->endbyte;
  }

  value=(value&mask[bits])<<(32-bits);
  bits+=b->endbit;

  b->ptr[0]|=value>>(24+b->endbit);

  if(bits>=8){
    b->ptr[1]=(unsigned char)(value>>(16+b->endbit));
    if(bits>=16){
      b->ptr[2]=(unsigned char)(value>>(8+b->endbit));
      if(bits>=24){
        b->ptr[3]=(unsigned char)(value>>(b->endbit));
        if(bits>=32){
          if(b->endbit)
            b->ptr[4]=(unsigned char)(value<<(8-b->endbit));
          else
            b->ptr[4]=0;
        }
      }
    }
  }

  b->endbyte+=bits/8;
  b->ptr+=bits/8;
  b->endbit=bits&7;
  return;
 err:
  oggpack_writeclear(b);
}