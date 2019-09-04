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
 unsigned char* cp50221_0212_ext_page21 ; 
 unsigned char* cp50221_0212_ext_page53 ; 
 unsigned char* cp50221_0212_ext_page6d ; 
 unsigned char* cp50221_0212_ext_page76 ; 
 unsigned char* cp50221_0212_ext_page7d ; 
 unsigned char* cp50221_0212_ext_page97 ; 
 unsigned char* cp50221_0212_ext_pagefa ; 
 unsigned char* cp50221_0212_ext_pageff ; 

__attribute__((used)) static int
cp50221_0212_ext_wctomb (conv_t conv, unsigned char *r, ucs4_t wc, size_t n)
{
  unsigned char c = 0;
  if (wc >= 0x2170 && wc < 0x2180)
    c = cp50221_0212_ext_page21[wc-0x2170];
  else if (wc == 0x4efc)
    c = 0x1b;
  else if (wc == 0x50f4)
    c = 0x1c;
  else if (wc == 0x51ec)
    c = 0x1d;
  else if (wc >= 0x5300 && wc < 0x5328)
    c = cp50221_0212_ext_page53[wc-0x5300];
  else if (wc == 0x548a)
    c = 0x21;
  else if (wc == 0x5759)
    c = 0x22;
  else if (wc == 0x589e)
    c = 0x25;
  else if (wc == 0x5bec)
    c = 0x26;
  else if (wc == 0x5cf5)
    c = 0x27;
  else if (wc == 0x5d53)
    c = 0x28;
  else if (wc == 0x5fb7)
    c = 0x2a;
  else if (wc == 0x6085)
    c = 0x2b;
  else if (wc == 0x6120)
    c = 0x2c;
  else if (wc == 0x654e)
    c = 0x2d;
  else if (wc == 0x6665)
    c = 0x2f;
  else if (wc == 0x6801)
    c = 0x32;
  else if (wc == 0x6a6b)
    c = 0x35;
  else if (wc == 0x6ae2)
    c = 0x36;
  else if (wc >= 0x6df0 && wc < 0x6e00)
    c = cp50221_0212_ext_page6d[wc-0x6df0];
  else if (wc == 0x7028)
    c = 0x39;
  else if (wc == 0x70bb)
    c = 0x1a;
  else if (wc == 0x7501)
    c = 0x3c;
  else if (wc >= 0x7680 && wc < 0x76a0)
    c = cp50221_0212_ext_page76[wc-0x7680];
  else if (wc == 0x7930)
    c = 0x40;
  else if (wc == 0x7ae7)
    c = 0x45;
  else if (wc >= 0x7da0 && wc < 0x7dd8)
    c = cp50221_0212_ext_page7d[wc-0x7da0];
  else if (wc == 0x8362)
    c = 0x4b;
  else if (wc == 0x85b0)
    c = 0x4d;
  else if (wc == 0x8807)
    c = 0x50;
  else if (wc == 0x8b7f)
    c = 0x52;
  else if (wc == 0x8cf4)
    c = 0x53;
  else if (wc == 0x8d76)
    c = 0x54;
  else if (wc == 0x90de)
    c = 0x58;
  else if (wc == 0x9115)
    c = 0x5a;
  else if (wc == 0x9592)
    c = 0x5d;
  else if (wc >= 0x9738 && wc < 0x9758)
    c = cp50221_0212_ext_page97[wc-0x9738];
  else if (wc == 0x999e)
    c = 0x66;
  else if (wc == 0x9ad9)
    c = 0x67;
  else if (wc == 0x9b72)
    c = 0x68;
  else if (wc == 0x9ed1)
    c = 0x6a;
  else if (wc == 0xf929)
    c = 0x31;
  else if (wc == 0xf9dc)
    c = 0x5e;
  else if (wc >= 0xfa08 && wc < 0xfa30)
    c = cp50221_0212_ext_pagefa[wc-0xfa08];
  else if (wc >= 0xff00 && wc < 0xff08)
    c = cp50221_0212_ext_pageff[wc-0xff00];
  if (c != 0) {
    *r = c;
    return 1;
  }
  return RET_ILUNI;
}