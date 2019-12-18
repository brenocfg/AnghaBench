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
 int ascii_wctomb (int /*<<< orphan*/ ,unsigned char*,int,int) ; 
 int big5_wctomb (int /*<<< orphan*/ ,unsigned char*,int,int) ; 
 int cp950ext_wctomb (int /*<<< orphan*/ ,unsigned char*,int,int) ; 

__attribute__((used)) static int
cp950_wctomb (conv_t conv, unsigned char *r, ucs4_t wc, int n)
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
      if (wc == 0x00af) { buf[0] = 0xa1; buf[1] = 0xc2; ret = 2; break; }
      if (wc == 0x00a2 || wc == 0x00a3 || wc == 0x00a4)
        return RET_ILUNI;
      break;
    case 0x02:
      if (wc == 0x02cd) { buf[0] = 0xa1; buf[1] = 0xc5; ret = 2; break; }
      break;
    case 0x20:
      if (wc == 0x2027) { buf[0] = 0xa1; buf[1] = 0x45; ret = 2; break; }
      if (wc == 0x20ac) { buf[0] = 0xa3; buf[1] = 0xe1; ret = 2; break; }
      if (wc == 0x2022 || wc == 0x203e)
        return RET_ILUNI;
      break;
    case 0x22:
      if (wc == 0x2215) { buf[0] = 0xa2; buf[1] = 0x41; ret = 2; break; }
      if (wc == 0x2295) { buf[0] = 0xa1; buf[1] = 0xf2; ret = 2; break; }
      if (wc == 0x2299) { buf[0] = 0xa1; buf[1] = 0xf3; ret = 2; break; }
      if (wc == 0x223c)
        return RET_ILUNI;
      break;
    case 0x25:
      if (wc == 0x2574) { buf[0] = 0xa1; buf[1] = 0x5a; ret = 2; break; }
      break;
    case 0x26:
      if (wc == 0x2609 || wc == 0x2641)
        return RET_ILUNI;
      break;
    case 0xe0: case 0xe1: case 0xe2: case 0xe3: case 0xe4: case 0xe5:
    case 0xe6: case 0xe7: case 0xe8: case 0xe9: case 0xea: case 0xeb:
    case 0xec: case 0xed: case 0xee: case 0xef: case 0xf0: case 0xf1:
    case 0xf2: case 0xf3: case 0xf4: case 0xf5: case 0xf6:
      {
        /* User-defined characters */
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
      if (wc == 0xff3c) { buf[0] = 0xa2; buf[1] = 0x40; ret = 2; break; }
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
    if (!((buf[0] == 0xc6 && buf[1] >= 0xa1) || buf[0] == 0xc7)) {
      if (n < 2)
        return RET_TOOSMALL;
      r[0] = buf[0];
      r[1] = buf[1];
      return 2;
    }
  }
  ret = cp950ext_wctomb(conv,buf,wc,2);
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