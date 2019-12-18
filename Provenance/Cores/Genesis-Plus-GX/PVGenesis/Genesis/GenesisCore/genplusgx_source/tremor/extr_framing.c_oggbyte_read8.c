#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {unsigned char* ptr; size_t pos; } ;
typedef  TYPE_1__ oggbyte_buffer ;
typedef  int ogg_int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  _positionB (TYPE_1__*,int) ; 
 int /*<<< orphan*/  _positionF (TYPE_1__*,int) ; 

__attribute__((used)) static ogg_int64_t oggbyte_read8(oggbyte_buffer *b,int pos){
  ogg_int64_t ret;
  unsigned char t[7];
  int i;
  _positionB(b,pos);
  for(i=0;i<7;i++){
    _positionF(b,pos);
    t[i]=b->ptr[pos++ -b->pos];
  }

  _positionF(b,pos);
  ret=b->ptr[pos-b->pos];

  for(i=6;i>=0;--i)
    ret= ret<<8 | t[i];

  return ret;
}