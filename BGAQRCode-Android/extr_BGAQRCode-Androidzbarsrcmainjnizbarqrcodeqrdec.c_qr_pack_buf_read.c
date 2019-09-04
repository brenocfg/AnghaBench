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
struct TYPE_3__ {int endbit; int storage; int endbyte; unsigned char* buf; } ;
typedef  TYPE_1__ qr_pack_buf ;

/* Variables and functions */

__attribute__((used)) static int qr_pack_buf_read(qr_pack_buf *_b,int _bits){
  const unsigned char *p;
  unsigned             ret;
  int                  m;
  int                  d;
  m=16-_bits;
  _bits+=_b->endbit;
  d=_b->storage-_b->endbyte;
  if(d<=2){
    /*Not the main path.*/
    if(d*8<_bits){
      _b->endbyte+=_bits>>3;
      _b->endbit=_bits&7;
      return -1;
    }
    /*Special case to avoid reading p[0] below, which might be past the end of
       the buffer; also skips some useless accounting.*/
    else if(!_bits)return 0;
  }
  p=_b->buf+_b->endbyte;
  ret=p[0]<<8+_b->endbit;
  if(_bits>8){
    ret|=p[1]<<_b->endbit;
    if(_bits>16)ret|=p[2]>>8-_b->endbit;
  }
  _b->endbyte+=_bits>>3;
  _b->endbit=_bits&7;
  return (ret&0xFFFF)>>m;
}