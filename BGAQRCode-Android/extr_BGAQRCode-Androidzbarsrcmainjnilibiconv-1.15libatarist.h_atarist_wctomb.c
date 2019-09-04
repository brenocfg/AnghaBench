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
 unsigned char* atarist_page00 ; 
 unsigned char* atarist_page01 ; 
 unsigned char* atarist_page03 ; 
 unsigned char* atarist_page05 ; 
 unsigned char* atarist_page22 ; 
 unsigned char* atarist_page23 ; 

__attribute__((used)) static int
atarist_wctomb (conv_t conv, unsigned char *r, ucs4_t wc, size_t n)
{
  unsigned char c = 0;
  if (wc < 0x0080) {
    *r = wc;
    return 1;
  }
  else if (wc >= 0x00a0 && wc < 0x0100)
    c = atarist_page00[wc-0x00a0];
  else if (wc >= 0x0130 && wc < 0x0198)
    c = atarist_page01[wc-0x0130];
  else if (wc >= 0x0390 && wc < 0x03c8)
    c = atarist_page03[wc-0x0390];
  else if (wc >= 0x05d0 && wc < 0x05f0)
    c = atarist_page05[wc-0x05d0];
  else if (wc == 0x2020)
    c = 0xbb;
  else if (wc == 0x207f)
    c = 0xfc;
  else if (wc == 0x2122)
    c = 0xbf;
  else if (wc >= 0x2208 && wc < 0x2268)
    c = atarist_page22[wc-0x2208];
  else if (wc >= 0x2310 && wc < 0x2328)
    c = atarist_page23[wc-0x2310];
  if (c != 0) {
    *r = c;
    return 1;
  }
  return RET_ILUNI;
}