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
 scalar_t__ bmp_only ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned int const) ; 
 int strlen (char*) ; 

__attribute__((used)) static const char* ucs4_decode (const unsigned int* out, unsigned int outlen)
{
  static char hexbuf[21];
  char* p = hexbuf;
  while (outlen > 0) {
    if (p > hexbuf)
      *p++ = ' ';
    sprintf (p, "0x%04X", out[0]);
    out += 1; outlen -= 1;
    if (bmp_only && strlen(p) > 6)
      return NULL;
    p += strlen(p);
  }
  return hexbuf;
}