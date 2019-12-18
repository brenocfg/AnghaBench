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
 int BSWAP16L (int) ; 
 int BSWAP32 (int) ; 
 int /*<<< orphan*/  T1WriteByte (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  T1WriteLong (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  T1WriteWord (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  VidsoftWaitForVdp1Thread () ; 
 int /*<<< orphan*/  vdp1backframebuffer ; 

void VIDSoftVdp1WriteFrameBuffer(u32 type, u32 addr, u32 val)
{
   VidsoftWaitForVdp1Thread();

   switch (type)
   {
   case 0:
      T1WriteByte(vdp1backframebuffer, addr, val);
      break;
   case 1:
#ifndef WORDS_BIGENDIAN
      val = BSWAP16L(val);
#endif
      T1WriteWord(vdp1backframebuffer, addr, val);
      break;
   case 2:
#ifndef WORDS_BIGENDIAN
      val = BSWAP32(val);
#endif
      val = (val & 0xffff) << 16 | (val & 0xffff0000) >> 16;
      T1WriteLong(vdp1backframebuffer, addr, val);
      break;
   default:
      break;
   }
}