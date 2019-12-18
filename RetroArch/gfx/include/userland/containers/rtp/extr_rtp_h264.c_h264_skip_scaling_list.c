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
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ int32_t ;
typedef  int /*<<< orphan*/  VC_CONTAINER_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_BITS_T ;

/* Variables and functions */
 scalar_t__ BITS_READ_S32_EXP (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void h264_skip_scaling_list(VC_CONTAINER_T *p_ctx,
      VC_CONTAINER_BITS_T *sprop,
      uint32_t size_of_scaling_list)
{
   uint32_t last_scale = 8;
   uint32_t next_scale = 8;
   int32_t delta_scale;
   uint32_t jj;

   /* Algorithm taken from H.264 section 7.3.2.1.1.1 */
   for (jj = 0; jj < size_of_scaling_list; jj++)
   {
      if (next_scale)
      {
         delta_scale = BITS_READ_S32_EXP(p_ctx, sprop, "delta_scale");
         next_scale = (last_scale + delta_scale + 256) & 0xFF;

         if (next_scale)
            last_scale = next_scale;
      }
   }
}