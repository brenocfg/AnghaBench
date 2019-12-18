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
typedef  int /*<<< orphan*/  byte ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

void
_mesa_upscale_teximage2d (unsigned int inWidth, unsigned int inHeight,
			  unsigned int outWidth, unsigned int outHeight,
			  unsigned int comps,
			  const byte *src, int srcRowStride,
			  byte *dest)
{
    unsigned int i, j, k;

    assert(outWidth >= inWidth);
    assert(outHeight >= inHeight);

#if 1 /* H.Morii - faster loops */
  for (i = 0; i < inHeight; i++) {
    for (j = 0; j < inWidth; j++) {
      const int aa = (i * outWidth + j) * comps;
      const int bb = i * srcRowStride + j * comps;
      for (k = 0; k < comps; k++) {
        dest[aa + k] = src[bb + k];
      }
    }
    for (; j < outWidth; j++) {
      const int aa = (i * outWidth + j) * comps;
      const int bb = i * srcRowStride + (j - inWidth) * comps;
      for (k = 0; k < comps; k++) {
        dest[aa + k] = src[bb + k];
      }
    }
  }
  for (; i < outHeight; i++) {
    for (j = 0; j < inWidth; j++) {
      const int aa = (i * outWidth + j) * comps;
      const int bb = (i - inHeight) * srcRowStride + j * comps;
      for (k = 0; k < comps; k++) {
        dest[aa + k] = src[bb + k];
      }
    }
    for (; j < outWidth; j++) {
      const int aa = (i * outWidth + j) * comps;
      const int bb = (i - inHeight) * srcRowStride + (j - inWidth) * comps;
      for (k = 0; k < comps; k++) {
        dest[aa + k] = src[bb + k];
      }
    }
  }
#else
    for (i = 0; i < outHeight; i++) {
	const int ii = i % inHeight;
	for (j = 0; j < outWidth; j++) {
	    const int jj = j % inWidth;
            const int aa = (i * outWidth + j) * comps;
            const int bb = ii * srcRowStride + jj * comps;
	    for (k = 0; k < comps; k++) {
		dest[aa + k] = src[bb + k];
	    }
	}
    }
#endif
}