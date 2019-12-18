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
typedef  void* uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  __m128i ;

/* Variables and functions */
 int /*<<< orphan*/  _mm_loadu_si128 (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  store_bgr24_sse2 (void**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void conv_argb8888_bgr24(void *output_, const void *input_,
      int width, int height,
      int out_stride, int in_stride)
{
   int h;
   const uint32_t *input = (const uint32_t*)input_;
   uint8_t *output       = (uint8_t*)output_;

#if defined(__SSE2__)
   int max_width = width - 15;
#endif

   for (h = 0; h < height;
         h++, output += out_stride, input += in_stride >> 2)
   {
      uint8_t *out = output;
      int        w = 0;
#if defined(__SSE2__)
      for (; w < max_width; w += 16, out += 48)
      {
         __m128i l0 = _mm_loadu_si128((const __m128i*)(input + w +  0));
         __m128i l1 = _mm_loadu_si128((const __m128i*)(input + w +  4));
         __m128i l2 = _mm_loadu_si128((const __m128i*)(input + w +  8));
         __m128i l3 = _mm_loadu_si128((const __m128i*)(input + w + 12));
         store_bgr24_sse2(out, l0, l1, l2, l3);
      }
#endif

      for (; w < width; w++)
      {
         uint32_t col = input[w];
         *out++       = (uint8_t)(col >>  0);
         *out++       = (uint8_t)(col >>  8);
         *out++       = (uint8_t)(col >> 16);
      }
   }
}