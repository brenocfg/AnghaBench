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
typedef  int ucs4_t ;
typedef  int /*<<< orphan*/  conv_t ;

/* Variables and functions */
 int RET_ILUNI ; 
 int RET_TOOSMALL ; 
 int /*<<< orphan*/  abort () ; 
 int ascii_wctomb (int /*<<< orphan*/ ,unsigned char*,int,size_t) ; 
 unsigned char* big5_2003_2charset_page25 ; 
 int big5_wctomb (int /*<<< orphan*/ ,unsigned char*,int,int) ; 

__attribute__((used)) static int
big5_2003_wctomb (conv_t conv, unsigned char *r, ucs4_t wc, size_t n)
{
  unsigned char buf[2];
  int ret;

  /* Code set 0 (ASCII) */
  ret = ascii_wctomb(conv,r,wc,n);
  if (ret != RET_ILUNI)
    return ret;

  /* Code set 1 (BIG5 extended) */
  switch (wc >> 8) {
    case 0x00:
      if (wc == 0x00a8) { buf[0] = 0xc6; buf[1] = 0xd8; ret = 2; break; }
      if (wc == 0x00a2 || wc == 0x00a3 || wc == 0x00a5)
        return RET_ILUNI;
      break;
    case 0x02:
      if (wc == 0x02cd) { buf[0] = 0xa1; buf[1] = 0xc5; ret = 2; break; }
      break;
    case 0x04:
      return RET_ILUNI;
    case 0x20:
      if (wc == 0x2015) { buf[0] = 0xa1; buf[1] = 0x56; ret = 2; break; }
      if (wc == 0x2027) { buf[0] = 0xa1; buf[1] = 0x45; ret = 2; break; }
      if (wc == 0x20ac) { buf[0] = 0xa3; buf[1] = 0xe1; ret = 2; break; }
      if (wc == 0x2013 || wc == 0x2022)
        return RET_ILUNI;
      break;
    case 0x21:
      if (wc >= 0x2170 && wc <= 0x2179) {
        buf[0] = 0xc6; buf[1] = wc - 0x20bb; ret = 2;
        break;
      }
      break;
    case 0x22:
      if (wc == 0x2215) { buf[0] = 0xa2; buf[1] = 0x41; ret = 2; break; }
      if (wc == 0x2295) { buf[0] = 0xa1; buf[1] = 0xf2; ret = 2; break; }
      if (wc == 0x2299) { buf[0] = 0xa1; buf[1] = 0xf3; ret = 2; break; }
      if (wc == 0x223c)
        return RET_ILUNI;
      break;
    case 0x24:
      if (wc <= 0x241f) { buf[0] = 0xa3; buf[1] = wc - 0x2340; ret = 2; break; }
      if (wc == 0x2421) { buf[0] = 0xa3; buf[1] = 0xe0; ret = 2; break; }
      if (wc >= 0x2460 && wc <= 0x2469) {
        buf[0] = 0xc6; buf[1] = wc - 0x23bf; ret = 2;
        break;
      }
      if (wc >= 0x2474 && wc <= 0x247d) {
        buf[0] = 0xc6; buf[1] = wc - 0x23c9; ret = 2;
        break;
      }
      break;
    case 0x25:
      if (wc == 0x2501) { buf[0] = 0xa2; buf[1] = 0xa4; ret = 2; break; }
      if (wc == 0x251d) { buf[0] = 0xa2; buf[1] = 0xa5; ret = 2; break; }
      if (wc == 0x2525) { buf[0] = 0xa2; buf[1] = 0xa7; ret = 2; break; }
      if (wc == 0x253f) { buf[0] = 0xa2; buf[1] = 0xa6; ret = 2; break; }
      if (wc >= 0x2550 && wc <= 0x256c) {
        buf[0] = 0xf9; buf[1] = big5_2003_2charset_page25[wc-0x2550]; ret = 2;
        break;
      }
      if (wc == 0x2574) { buf[0] = 0xa1; buf[1] = 0x5a; ret = 2; break; }
      if (wc == 0x2593) { buf[0] = 0xf9; buf[1] = 0xfe; ret = 2; break; }
      break;
    case 0x26:
      if (wc == 0x2609 || wc == 0x2641)
        return RET_ILUNI;
      break;
    case 0x27:
      if (wc == 0x273d) { buf[0] = 0xc6; buf[1] = 0xe6; ret = 2; break; }
      break;
    case 0x2f:
      if (wc == 0x2f02) { buf[0] = 0xc6; buf[1] = 0xbf; ret = 2; break; }
      if (wc == 0x2f03) { buf[0] = 0xc6; buf[1] = 0xc0; ret = 2; break; }
      if (wc == 0x2f05) { buf[0] = 0xc6; buf[1] = 0xc1; ret = 2; break; }
      if (wc == 0x2f07) { buf[0] = 0xc6; buf[1] = 0xc2; ret = 2; break; }
      if (wc == 0x2f0c) { buf[0] = 0xc6; buf[1] = 0xc3; ret = 2; break; }
      if (wc == 0x2f0d) { buf[0] = 0xc6; buf[1] = 0xc4; ret = 2; break; }
      if (wc == 0x2f0e) { buf[0] = 0xc6; buf[1] = 0xc5; ret = 2; break; }
      if (wc == 0x2f13) { buf[0] = 0xc6; buf[1] = 0xc6; ret = 2; break; }
      if (wc == 0x2f16) { buf[0] = 0xc6; buf[1] = 0xc7; ret = 2; break; }
      if (wc == 0x2f19) { buf[0] = 0xc6; buf[1] = 0xc8; ret = 2; break; }
      if (wc == 0x2f1b) { buf[0] = 0xc6; buf[1] = 0xc9; ret = 2; break; }
      if (wc == 0x2f22) { buf[0] = 0xc6; buf[1] = 0xca; ret = 2; break; }
      if (wc == 0x2f27) { buf[0] = 0xc6; buf[1] = 0xcb; ret = 2; break; }
      if (wc == 0x2f2e) { buf[0] = 0xc6; buf[1] = 0xcc; ret = 2; break; }
      if (wc == 0x2f33) { buf[0] = 0xc6; buf[1] = 0xcd; ret = 2; break; }
      if (wc == 0x2f34) { buf[0] = 0xc6; buf[1] = 0xce; ret = 2; break; }
      if (wc == 0x2f35) { buf[0] = 0xc6; buf[1] = 0xcf; ret = 2; break; }
      if (wc == 0x2f39) { buf[0] = 0xc6; buf[1] = 0xd0; ret = 2; break; }
      if (wc == 0x2f3a) { buf[0] = 0xc6; buf[1] = 0xd1; ret = 2; break; }
      if (wc == 0x2f41) { buf[0] = 0xc6; buf[1] = 0xd2; ret = 2; break; }
      if (wc == 0x2f46) { buf[0] = 0xc6; buf[1] = 0xd3; ret = 2; break; }
      if (wc == 0x2f67) { buf[0] = 0xc6; buf[1] = 0xd4; ret = 2; break; }
      if (wc == 0x2f68) { buf[0] = 0xc6; buf[1] = 0xd5; ret = 2; break; }
      if (wc == 0x2fa1) { buf[0] = 0xc6; buf[1] = 0xd6; ret = 2; break; }
      if (wc == 0x2faa) { buf[0] = 0xc6; buf[1] = 0xd7; ret = 2; break; }
      break;
    case 0x30:
      if (wc >= 0x3005 && wc <= 0x3007) {
        buf[0] = 0xc6; buf[1] = wc - 0x2f25; ret = 2;
        break;
      }
      if (wc >= 0x3038 && wc <= 0x303a) {
        buf[0] = 0xa2; buf[1] = wc - 0x2f6c; ret = 2;
        break;
      }
      if (wc >= 0x3041 && wc <= 0x3093) {
        if (wc < 0x3059) {
          buf[0] = 0xc6; buf[1] = wc - 0x2f5a;
        } else {
          buf[0] = 0xc7; buf[1] = wc - 0x3019;
        }
        ret = 2;
        break;
      }
      if (wc == 0x309d) { buf[0] = 0xc6; buf[1] = 0xdc; ret = 2; break; }
      if (wc == 0x309e) { buf[0] = 0xc6; buf[1] = 0xdd; ret = 2; break; }
      if (wc >= 0x30a1 && wc <= 0x30f6) {
        buf[0] = 0xc7; buf[1] = wc - (wc < 0x30a5 ? 0x3026 : 0x3004); ret = 2;
        break;
      }
      if (wc == 0x30fc) { buf[0] = 0xc6; buf[1] = 0xe3; ret = 2; break; }
      if (wc == 0x30fd) { buf[0] = 0xc6; buf[1] = 0xda; ret = 2; break; }
      if (wc == 0x30fe) { buf[0] = 0xc6; buf[1] = 0xdb; ret = 2; break; }
      break;
    case 0x53:
      if (wc == 0x5344)
        return RET_ILUNI;
      break;
    case 0x58:
      if (wc == 0x58bb) { buf[0] = 0xf9; buf[1] = 0xd9; ret = 2; break; }
      break;
    case 0x5a:
      if (wc == 0x5afa) { buf[0] = 0xf9; buf[1] = 0xdc; ret = 2; break; }
      break;
    case 0x5f:
      if (wc == 0x5f5e) { buf[0] = 0xc2; buf[1] = 0x55; ret = 2; break; }
      if (wc == 0x5f5d)
        return RET_ILUNI;
      break;
    case 0x60:
      if (wc == 0x6052) { buf[0] = 0xf9; buf[1] = 0xda; ret = 2; break; }
      break;
    case 0x78:
      if (wc == 0x7881) { buf[0] = 0xf9; buf[1] = 0xd6; ret = 2; break; }
      break;
    case 0x7c:
      if (wc == 0x7ca7) { buf[0] = 0xf9; buf[1] = 0xdb; ret = 2; break; }
      break;
    case 0x88:
      if (wc == 0x88cf) { buf[0] = 0xf9; buf[1] = 0xd8; ret = 2; break; }
      break;
    case 0x92:
      if (wc == 0x92b9) { buf[0] = 0xf9; buf[1] = 0xd7; ret = 2; break; }
      break;
    case 0xe0: case 0xe1: case 0xe2: case 0xe3: case 0xe4: case 0xe5:
    case 0xe6: case 0xe7: case 0xe8: case 0xe9: case 0xea: case 0xeb:
    case 0xec: case 0xed: case 0xee: case 0xef: case 0xf0: case 0xf1:
    case 0xf2: case 0xf3: case 0xf4: case 0xf5: case 0xf6:
      {
        unsigned int i = wc - 0xe000;
        if (i < 5809) {
          unsigned int c1 = i / 157;
          unsigned int c2 = i % 157;
          buf[0] = c1 + (c1 < 5 ? 0xfa : c1 < 24 ? 0x89 : 0x69);
          buf[1] = c2 + (c2 < 0x3f ? 0x40 : 0x62);
          ret = 2;
          break;
        }
      }
      break;
    case 0xfe:
      if (wc == 0xfe51) { buf[0] = 0xa1; buf[1] = 0x4e; ret = 2; break; }
      if (wc == 0xfe68) { buf[0] = 0xa2; buf[1] = 0x42; ret = 2; break; }
      break;
    case 0xff:
      if (wc == 0xff0f) { buf[0] = 0xa1; buf[1] = 0xfe; ret = 2; break; }
      if (wc == 0xff3b) { buf[0] = 0xc6; buf[1] = 0xe4; ret = 2; break; }
      if (wc == 0xff3c) { buf[0] = 0xa2; buf[1] = 0x40; ret = 2; break; }
      if (wc == 0xff3d) { buf[0] = 0xc6; buf[1] = 0xe5; ret = 2; break; }
      if (wc == 0xff3e) { buf[0] = 0xc6; buf[1] = 0xd9; ret = 2; break; }
      if (wc == 0xff5e) { buf[0] = 0xa1; buf[1] = 0xe3; ret = 2; break; }
      if (wc == 0xffe0) { buf[0] = 0xa2; buf[1] = 0x46; ret = 2; break; }
      if (wc == 0xffe1) { buf[0] = 0xa2; buf[1] = 0x47; ret = 2; break; }
      if (wc == 0xffe3) { buf[0] = 0xa1; buf[1] = 0xc3; ret = 2; break; }
      if (wc == 0xffe5) { buf[0] = 0xa2; buf[1] = 0x44; ret = 2; break; }
      if (wc == 0xff64)
        return RET_ILUNI;
      break;
  }
  if (ret == RET_ILUNI)
    ret = big5_wctomb(conv,buf,wc,2);
  if (ret != RET_ILUNI) {
    if (ret != 2) abort();
    if (n < 2)
      return RET_TOOSMALL;
    r[0] = buf[0];
    r[1] = buf[1];
    return 2;
  }

  return RET_ILUNI;
}