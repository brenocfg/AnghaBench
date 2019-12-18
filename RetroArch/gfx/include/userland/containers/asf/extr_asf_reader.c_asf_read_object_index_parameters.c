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
typedef  int int64_t ;
typedef  int /*<<< orphan*/  VC_CONTAINER_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_STATUS_T ;

/* Variables and functions */
 scalar_t__ ASF_READ_U16 (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  ASF_SKIP_U16 (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  ASF_SKIP_U32 (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  CHECK_POINT (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  STREAM_STATUS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VC_CONTAINER_ERROR_CORRUPTED ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T asf_read_object_index_parameters( VC_CONTAINER_T *p_ctx, int64_t size )
{
#ifdef ENABLE_CONTAINERS_LOG_FORMAT
   /* This is added for debugging only. The spec (section 4.9) states that this is also enclosed in
    * the index object (see above) and that they are identical. I think they aren't always... */
   uint32_t i, specifiers_count;

   /* Read the time interval in milliseconds */
   ASF_SKIP_U32(p_ctx, size, "Index Entry Time Interval");

   specifiers_count = (uint32_t)ASF_READ_U16(p_ctx, size, "Index Specifiers Count");

   CHECK_POINT(p_ctx, size);

   /* Index specifiers. Search for the one we like best */
   if(size < specifiers_count * 4) return VC_CONTAINER_ERROR_CORRUPTED;
   for(i = 0; i < specifiers_count; i++)
   {
      ASF_SKIP_U16(p_ctx, size, "Stream Number");
      ASF_SKIP_U16(p_ctx, size, "Index Type");
   }
#endif
   CHECK_POINT(p_ctx, size);

   return STREAM_STATUS(p_ctx);
}