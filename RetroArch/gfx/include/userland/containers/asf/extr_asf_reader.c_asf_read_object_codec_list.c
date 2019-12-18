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
 int /*<<< orphan*/  ASF_SKIP_STRING (int /*<<< orphan*/ *,scalar_t__,scalar_t__,char*) ; 
 int /*<<< orphan*/  ASF_SKIP_U16 (int /*<<< orphan*/ *,scalar_t__,char*) ; 
 int /*<<< orphan*/  CHECK_POINT (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  VC_CONTAINER_ERROR_CORRUPTED ; 
 int /*<<< orphan*/  VC_CONTAINER_SUCCESS ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T asf_read_object_codec_list( VC_CONTAINER_T *p_ctx, int64_t size )
{
   VC_CONTAINER_STATUS_T status = VC_CONTAINER_SUCCESS;
   uint32_t i, count, length;

   ASF_SKIP_GUID(p_ctx, size, "Reserved");
   count = ASF_READ_U32(p_ctx, size, "Codec Entries Count");

   CHECK_POINT(p_ctx, size);

   /* Codec entries */
   for(i = 0; i < count; i++)
   {
      ASF_SKIP_U16(p_ctx, size, "Type");
      length = ASF_READ_U16(p_ctx, size, "Codec Name Length");
      if(size < length) return VC_CONTAINER_ERROR_CORRUPTED;
      ASF_SKIP_STRING(p_ctx, size, length * 2, "Codec Name");
      length = ASF_READ_U16(p_ctx, size, "Codec Description Length");
      if(size < length) return VC_CONTAINER_ERROR_CORRUPTED;
      ASF_SKIP_STRING(p_ctx, size, length * 2, "Codec Description");
      length = ASF_READ_U16(p_ctx, size, "Codec Information Length");
      if(size < length) return VC_CONTAINER_ERROR_CORRUPTED;
      ASF_SKIP_BYTES(p_ctx, size, length);

      CHECK_POINT(p_ctx, size);
   }

   return status;
}