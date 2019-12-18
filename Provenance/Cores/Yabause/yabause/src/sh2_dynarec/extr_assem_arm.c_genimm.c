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

u32 genimm(u32 imm,u32 *encoded)
{
  if(imm==0) {*encoded=0;return 1;}
  int i=32;
  while(i>0)
  {
    if(imm<256) {
      *encoded=((i&30)<<7)|imm;
      return 1;
    }
    imm=(imm>>2)|(imm<<30);i-=2;
  }
  return 0;
}