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
typedef  scalar_t__ int64_t ;
typedef  int /*<<< orphan*/  VC_CONTAINER_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_STATUS_T ;

/* Variables and functions */
 scalar_t__ ASF_READ_U16 (int /*<<< orphan*/ *,scalar_t__,char*) ; 
 scalar_t__ ASF_READ_U32 (int /*<<< orphan*/ *,scalar_t__,char*) ; 
 int /*<<< orphan*/  ASF_SKIP_BYTES (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ASF_SKIP_GUID (int /*<<< orphan*/ *,scalar_t__,char*) ; 
 int /*<<< orphan*/  ASF_SKIP_U16 (int /*<<< orphan*/ *,scalar_t__,char*) ; 
 int /*<<< orphan*/  ASF_SKIP_U32 (int /*<<< orphan*/ *,scalar_t__,char*) ; 
 int /*<<< orphan*/  CHECK_POINT (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  STREAM_STATUS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VC_CONTAINER_ERROR_CORRUPTED ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T asf_read_object_adv_content_encryption( VC_CONTAINER_T *p_ctx, int64_t size )
{
   uint32_t i, count;

   count = ASF_READ_U16(p_ctx, size, "Content Encryption Records Count");

   for(i = 0; i < count; i++)
   {
      uint32_t j, rec_count, data_size, length;

      ASF_SKIP_GUID(p_ctx, size, "System ID");
      ASF_SKIP_U32(p_ctx, size, "System Version");
      rec_count = ASF_READ_U16(p_ctx, size, "Encrypted Object Record Count");

      CHECK_POINT(p_ctx, size);

      for(j = 0; j < rec_count; j++)
      {
         ASF_SKIP_U16(p_ctx, size, "Encrypted Object ID Type");
         length = ASF_READ_U16(p_ctx, size, "Encrypted Object ID Length");
         if(length > size) return VC_CONTAINER_ERROR_CORRUPTED;
         ASF_SKIP_BYTES(p_ctx, size, length);
         CHECK_POINT(p_ctx, size);
      }

      data_size = ASF_READ_U32(p_ctx, size, "Data Size");
      if(data_size > size) return VC_CONTAINER_ERROR_CORRUPTED;
      ASF_SKIP_BYTES(p_ctx, size, data_size);
      CHECK_POINT(p_ctx, size);
   }

   return STREAM_STATUS(p_ctx);
}