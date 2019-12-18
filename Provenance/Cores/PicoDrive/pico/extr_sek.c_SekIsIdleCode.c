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
 int PAHW_32X ; 
 int PAHW_MCD ; 
 int PicoAHW ; 

int SekIsIdleCode(unsigned short *dst, int bytes)
{
  // printf("SekIsIdleCode %04x %i\n", *dst, bytes);
  switch (bytes)
  {
    case 2:
      if ((*dst & 0xf000) != 0x6000)     // not another branch
        return 1;
      break;
    case 4:
      if ( (*dst & 0xff3f) == 0x4a38 || // tst.x ($xxxx.w); tas ($xxxx.w)
           (*dst & 0xc1ff) == 0x0038 || // move.x ($xxxx.w), dX
           (*dst & 0xf13f) == 0xb038)   // cmp.x ($xxxx.w), dX
        return 1;
      if (PicoAHW & (PAHW_MCD|PAHW_32X))
        break;
      // with no addons, there should be no need to wait
      // for byte change anywhere
      if ( (*dst & 0xfff8) == 0x4a10 || // tst.b ($aX)
           (*dst & 0xfff8) == 0x4a28)   // tst.b ($xxxx,a0)
        return 1;
      break;
    case 6:
      if ( ((dst[1] & 0xe0) == 0xe0 && ( // RAM and
            *dst == 0x4a39 ||            //   tst.b ($xxxxxxxx)
            *dst == 0x4a79 ||            //   tst.w ($xxxxxxxx)
            *dst == 0x4ab9 ||            //   tst.l ($xxxxxxxx)
            (*dst & 0xc1ff) == 0x0039 || //   move.x ($xxxxxxxx), dX
            (*dst & 0xf13f) == 0xb039))||//   cmp.x ($xxxxxxxx), dX
            *dst == 0x0838 ||            // btst $X, ($xxxx.w) [6 byte op]
            (*dst & 0xffbf) == 0x0c38)   // cmpi.{b,w} $X, ($xxxx.w)
        return 1;
      break;
    case 8:
      if ( ((dst[2] & 0xe0) == 0xe0 && ( // RAM and
            *dst == 0x0839 ||            //   btst $X, ($xxxxxxxx.w) [8 byte op]
            (*dst & 0xffbf) == 0x0c39))||//   cmpi.{b,w} $X, ($xxxxxxxx)
            *dst == 0x0cb8)              // cmpi.l $X, ($xxxx.w)
        return 1;
      break;
    case 12:
      if (PicoAHW & (PAHW_MCD|PAHW_32X))
        break;
      if ( (*dst & 0xf1f8) == 0x3010 && // move.w (aX), dX
            (dst[1]&0xf100) == 0x0000 && // arithmetic
            (dst[3]&0xf100) == 0x0000)   // arithmetic
        return 1;
      break;
  }

  return 0;
}