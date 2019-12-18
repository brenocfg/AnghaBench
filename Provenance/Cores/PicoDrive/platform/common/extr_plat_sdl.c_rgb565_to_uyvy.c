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
 int* yuv_by ; 
 int* yuv_gy ; 
 int* yuv_ry ; 
 unsigned char* yuv_u ; 
 unsigned char* yuv_v ; 

void rgb565_to_uyvy(void *d, const void *s, int pixels)
{
  unsigned int *dst = d;
  const unsigned short *src = s;
  const unsigned char *yu = yuv_u + 32;
  const unsigned char *yv = yuv_v + 32;
  int r0, g0, b0, r1, g1, b1;
  int y0, y1, u, v;

  for (; pixels > 0; src += 2, dst++, pixels -= 2)
  {
    r0 = (src[0] >> 11) & 0x1f;
    g0 = (src[0] >> 6) & 0x1f;
    b0 =  src[0] & 0x1f;
    r1 = (src[1] >> 11) & 0x1f;
    g1 = (src[1] >> 6) & 0x1f;
    b1 =  src[1] & 0x1f;
    y0 = (yuv_ry[r0] + yuv_gy[g0] + yuv_by[b0]) >> 16;
    y1 = (yuv_ry[r1] + yuv_gy[g1] + yuv_by[b1]) >> 16;
    u = yu[b0 - y0];
    v = yv[r0 - y0];
    // valid Y range seems to be 16..235
    y0 = 16 + 219 * y0 / 31;
    y1 = 16 + 219 * y1 / 31;

    *dst = (y1 << 24) | (v << 16) | (y0 << 8) | u;
  }
}