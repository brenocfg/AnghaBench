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
 unsigned char* cp50221_0208_ext_page21 ; 
 unsigned char* cp50221_0208_ext_page22 ; 
 unsigned char* cp50221_0208_ext_page24 ; 
 unsigned char* cp50221_0208_ext_page30 ; 
 unsigned char* cp50221_0208_ext_page32 ; 
 unsigned char* cp50221_0208_ext_page32_1 ; 
 unsigned char* cp50221_0208_ext_page33 ; 

__attribute__((used)) static int
cp50221_0208_ext_wctomb (conv_t conv, unsigned char *r, ucs4_t wc, size_t n)
{
  unsigned char c = 0;
  if (wc >= 0x2110 && wc < 0x2170)
    c = cp50221_0208_ext_page21[wc-0x2110];
  else if (wc >= 0x2210 && wc < 0x2230)
    c = cp50221_0208_ext_page22[wc-0x2210];
  else if (wc == 0x22bf)
    c = 0x59;
  else if (wc >= 0x2460 && wc < 0x2478)
    c = cp50221_0208_ext_page24[wc-0x2460];
  else if (wc >= 0x3018 && wc < 0x3020)
    c = cp50221_0208_ext_page30[wc-0x3018];
  else if (wc >= 0x3230 && wc < 0x3240)
    c = cp50221_0208_ext_page32[wc-0x3230];
  else if (wc >= 0x32a0 && wc < 0x32b0)
    c = cp50221_0208_ext_page32_1[wc-0x32a0];
  else if (wc >= 0x3300 && wc < 0x33d0)
    c = cp50221_0208_ext_page33[wc-0x3300];
  if (c != 0) {
    *r = c;
    return 1;
  }
  return RET_ILUNI;
}