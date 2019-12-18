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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  VC_CONTAINER_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_BITS_T ;

/* Variables and functions */
 int BITS_READ_U32 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,char*) ; 

__attribute__((used)) static int32_t mp4_flagged_delta(VC_CONTAINER_T *p_ctx,
      VC_CONTAINER_BITS_T *au_headers,
      uint32_t delta_length)
{
   uint32_t value = 0;

   /* Flag is only present if the delta length is non-zero */
   if (delta_length && BITS_READ_U32(p_ctx, au_headers, 1, "CTS/DTS delta present"))
   {
      value = BITS_READ_U32(p_ctx, au_headers, delta_length, "CTS/DTS delta");

      /* Sign extend value based on bit length */
      if (value & (1 << (delta_length - 1)))
         value |= ~((1 << delta_length) - 1);
   }

   return (int32_t)value;
}