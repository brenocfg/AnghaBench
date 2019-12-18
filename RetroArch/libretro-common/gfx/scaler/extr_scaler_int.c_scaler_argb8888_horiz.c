#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int uint32_t ;
struct TYPE_4__ {int* filter; int* filter_pos; int filter_len; int /*<<< orphan*/  filter_stride; } ;
struct TYPE_3__ {int* frame; int height; int stride; int width; } ;
struct scaler_ctx {TYPE_2__ horiz; TYPE_1__ scaled; } ;
typedef  int int16_t ;
typedef  int /*<<< orphan*/  __m128i ;

/* Variables and functions */
 int /*<<< orphan*/  _mm_adds_epi16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* _mm_cvtsi128_si32 (int /*<<< orphan*/ ) ; 
 int _mm_cvtsi128_si64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _mm_mulhi_epi16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _mm_set_epi32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  _mm_set_epi64x (int const,int const) ; 
 int /*<<< orphan*/  _mm_setzero_si128 () ; 
 int /*<<< orphan*/  _mm_slli_epi16 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  _mm_srli_si128 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  _mm_unpacklo_epi8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void scaler_argb8888_horiz(const struct scaler_ctx *ctx, const void *input_, int stride)
{
   int h, w, x;
   const uint32_t *input = (uint32_t*)input_;
   uint64_t *output      = ctx->scaled.frame;

   for (h = 0; h < ctx->scaled.height; h++, input += stride >> 2,
         output += ctx->scaled.stride >> 3)
   {
      const int16_t *filter_horiz = ctx->horiz.filter;

      for (w = 0; w < ctx->scaled.width; w++,
            filter_horiz += ctx->horiz.filter_stride)
      {
         const uint32_t *input_base_x = input + ctx->horiz.filter_pos[w];
#if defined(__SSE2__)
         __m128i res = _mm_setzero_si128();
#ifndef __x86_64__
         union
         {
            uint32_t *u32;
            uint64_t *u64;
         } u;
#endif
         for (x = 0; (x + 1) < ctx->horiz.filter_len; x += 2)
         {
            __m128i coeff = _mm_set_epi64x(filter_horiz[x + 1] * 0x0001000100010001ll, filter_horiz[x + 0] * 0x0001000100010001ll);

            __m128i col   = _mm_unpacklo_epi8(_mm_set_epi64x(0,
                     ((uint64_t)input_base_x[x + 1] << 32) | input_base_x[x + 0]), _mm_setzero_si128());

            col           = _mm_slli_epi16(col, 7);
            res           = _mm_adds_epi16(_mm_mulhi_epi16(col, coeff), res);
         }

         for (; x < ctx->horiz.filter_len; x++)
         {
            __m128i coeff = _mm_set_epi64x(0, filter_horiz[x] * 0x0001000100010001ll);
            __m128i col   = _mm_unpacklo_epi8(_mm_set_epi32(0, 0, 0, input_base_x[x]), _mm_setzero_si128());

            col           = _mm_slli_epi16(col, 7);
            res           = _mm_adds_epi16(_mm_mulhi_epi16(col, coeff), res);
         }

         res              = _mm_adds_epi16(_mm_srli_si128(res, 8), res);

#ifdef __x86_64__
         output[w]        = _mm_cvtsi128_si64(res);
#else /* 32-bit doesn't have si64. Do it in two steps. */
         u.u64    = output + w;
         u.u32[0] = _mm_cvtsi128_si32(res);
         u.u32[1] = _mm_cvtsi128_si32(_mm_srli_si128(res, 4));
#endif
#else
         int16_t res_a = 0;
         int16_t res_r = 0;
         int16_t res_g = 0;
         int16_t res_b = 0;

         for (x = 0; x < ctx->horiz.filter_len; x++)
         {
            uint32_t col   = input_base_x[x];

            int16_t a      = (col >> (24 - 7)) & (0xff << 7);
            int16_t r      = (col >> (16 - 7)) & (0xff << 7);
            int16_t g      = (col >> ( 8 - 7)) & (0xff << 7);
            int16_t b      = (col << ( 0 + 7)) & (0xff << 7);

            int16_t coeff  = filter_horiz[x];

            res_a         += (a * coeff) >> 16;
            res_r         += (r * coeff) >> 16;
            res_g         += (g * coeff) >> 16;
            res_b         += (b * coeff) >> 16;
         }

         output[w]         = (
               (uint64_t)res_a  << 48)  |
               ((uint64_t)res_r << 32)  |
               ((uint64_t)res_g << 16)  |
               ((uint64_t)res_b << 0);
#endif
      }
   }
}