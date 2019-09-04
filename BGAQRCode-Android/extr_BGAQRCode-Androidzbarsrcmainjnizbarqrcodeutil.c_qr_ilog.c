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

int qr_ilog(unsigned _v){
#if defined(QR_CLZ)
/*Note that __builtin_clz is not defined when _x==0, according to the gcc
   documentation (and that of the x86 BSR instruction that implements it), so
   we have to special-case it.*/
  return QR_CLZ0-QR_CLZ(_v)&-!!_v;
#else
  int ret;
  int m;
  m=!!(_v&0xFFFF0000)<<4;
  _v>>=m;
  ret=m;
  m=!!(_v&0xFF00)<<3;
  _v>>=m;
  ret|=m;
  m=!!(_v&0xF0)<<2;
  _v>>=m;
  ret|=m;
  m=!!(_v&0xC)<<1;
  _v>>=m;
  ret|=m;
  ret|=!!(_v&0x2);
  return ret + !!_v;
#endif
}