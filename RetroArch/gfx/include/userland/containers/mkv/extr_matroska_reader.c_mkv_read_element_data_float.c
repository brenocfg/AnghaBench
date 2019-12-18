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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int int64_t ;
typedef  int /*<<< orphan*/  VC_CONTAINER_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_STATUS_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_FORMAT (int /*<<< orphan*/ *,char*,double) ; 
 int /*<<< orphan*/  READ_U32 (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  READ_U64 (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  STREAM_STATUS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VC_CONTAINER_ERROR_CORRUPTED ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T mkv_read_element_data_float(VC_CONTAINER_T *p_ctx,
   int64_t size, double *value)
{
   union {
      uint32_t  u32;
      uint64_t  u64;
      float     f;
      double    d;
   } u;

   switch(size)
   {
   case 4: u.u32 = READ_U32(p_ctx, "f32-float"); *value = u.f; break;
   case 8: u.u64 = READ_U64(p_ctx, "f64-float"); *value = u.d; break;
   default: return VC_CONTAINER_ERROR_CORRUPTED;
   }
   LOG_FORMAT(p_ctx, "float: %f", *value);
   return STREAM_STATUS(p_ctx);
}