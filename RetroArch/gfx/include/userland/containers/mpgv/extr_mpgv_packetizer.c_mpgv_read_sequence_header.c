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
typedef  unsigned int int64_t ;
typedef  int /*<<< orphan*/  header ;
typedef  scalar_t__ VC_CONTAINER_STATUS_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_BYTESTREAM_T ;

/* Variables and functions */
 scalar_t__ VC_CONTAINER_ERROR_CORRUPTED ; 
 scalar_t__ VC_CONTAINER_SUCCESS ; 
 scalar_t__ bytestream_peek_at (int /*<<< orphan*/ *,size_t,int*,int) ; 
 unsigned int vc_container_maths_gcd (unsigned int,unsigned int) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T mpgv_read_sequence_header(VC_CONTAINER_BYTESTREAM_T *stream,
   size_t offset, unsigned int *width, unsigned int *height,
   unsigned int *frame_rate_num, unsigned int *frame_rate_den,
   unsigned int *aspect_ratio_num, unsigned int *aspect_ratio_den)
{
   static const int frame_rate[16][2] =
   { {0, 0}, {24000, 1001}, {24, 1}, {25, 1}, {30000, 1001}, {30, 1}, {50, 1},
     {60000, 1001}, {60, 1},
     /* Unofficial values */
     {15, 1001}, /* From Xing */
     {5, 1001}, {10, 1001}, {12, 1001}, {15, 1001} /* From libmpeg3 */ };
   static const int aspect_ratio[16][2] =
   { {0, 0}, {1, 1}, {4, 3}, {16, 9}, {221, 100} };

   VC_CONTAINER_STATUS_T status;
   unsigned int w, h, fr, ar;
   int64_t ar_num, ar_den, div;
   uint8_t header[8];

   status = bytestream_peek_at( stream, offset, header, sizeof(header));
   if(status != VC_CONTAINER_SUCCESS)
      return status;

   w = (header[4] << 4) | (header[5] >> 4);
   h = ((header[5]&0x0f) << 8) | header[6];
   ar = header[7] >> 4;
   fr = header[7]&0x0f;
   if (!w || !h || !ar || !fr)
      return VC_CONTAINER_ERROR_CORRUPTED;

   *width = w;
   *height = h;
   *frame_rate_num = frame_rate[fr][0];
   *frame_rate_den = frame_rate[fr][1];
   ar_num = (int64_t)aspect_ratio[ar][0] * h;
   ar_den = (int64_t)aspect_ratio[ar][1] * w;
   div = vc_container_maths_gcd(ar_num, ar_den);
   if (div)
   {
      ar_num /= div;
      ar_den /= div;
   }
   *aspect_ratio_num = ar_num;
   *aspect_ratio_den = ar_den;

   return VC_CONTAINER_SUCCESS;
}