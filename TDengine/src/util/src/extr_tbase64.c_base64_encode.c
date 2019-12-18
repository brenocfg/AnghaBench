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
 char* basis_64 ; 
 scalar_t__ malloc (size_t) ; 

char *base64_encode(const unsigned char *value, int vlen) {
  unsigned char oval = 0;
  char *        result = (char *)malloc((size_t)(vlen * 4) / 3 + 10);
  char *        out = result;
  while (vlen >= 3) {
    *out++ = basis_64[value[0] >> 2];
    *out++ = basis_64[((value[0] << 4) & 0x30) | (value[1] >> 4)];
    *out++ = basis_64[((value[1] << 2) & 0x3C) | (value[2] >> 6)];
    *out++ = basis_64[value[2] & 0x3F];
    value += 3;
    vlen -= 3;
  }
  if (vlen > 0) {
    *out++ = basis_64[value[0] >> 2];
    oval = (value[0] << 4) & 0x30;
    if (vlen > 1) oval |= value[1] >> 4;
    *out++ = basis_64[oval];
    *out++ = (vlen < 2) ? '=' : basis_64[(value[1] << 2) & 0x3C];
    *out++ = '=';
  }
  *out = '\0';
  return result;
}