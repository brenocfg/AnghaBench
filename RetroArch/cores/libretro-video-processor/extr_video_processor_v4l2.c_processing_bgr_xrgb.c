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
typedef  int uint8_t ;
typedef  int uint32_t ;

/* Variables and functions */

void processing_bgr_xrgb(uint8_t *src, uint32_t *dst, int width, int height) {
   /* BGR24 to XRGB8888 conversion */
   int i;
   for (i = 0; i < width * height; i+=1, src += 3, dst += 1) {
      *dst = 0xFF << 24 | src[2] << 16 | src[1] << 8 | src[0] << 0;
   }
}